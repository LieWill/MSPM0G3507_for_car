#include "task.h"
#include "pid.h"
#include "ti_msp_dl_config.h"
#include "rif.h"
#include "wit.h"
#include "OLED.h"

#define STRAGHT_DISTANCE 3300 // 直走距离
#define TURN_DISTANCE 3950	  // 大拐弯距离
#define SHORT_DISTANCE 2400	  // 小拐弯距离

#define FIRST_TURN 44.5  // 第一次旋转的角度
#define SECOND_TURN 74 // 第二次及以后旋转的角度

enum
{
	INS,	  // 惯性导航
	TARCKING, // 循迹
	STOP,	  // 停
} status = STOP;

static struct
{
	uint8_t _1;
	uint8_t _2;
	uint8_t _3;
	uint8_t _4;
	uint8_t _5;
} question_status = {0};

static uint8_t tu = 0;

extern float set_speed;

extern pid_wit angle;

extern pid_distance distance;

extern pid_rif rif;

extern bool isBlack;

volatile uint8_t Bee = 0;

void start_straight()
{
	distance.target = STRAGHT_DISTANCE + distance.real;
	angle.target = wit_get_yaw();
	status = INS;
	distance.limit = 5;
	delay_cycles(8000000);
	distance.limit = 10;
	delay_cycles(8000000);
	distance.limit = 15;
	delay_cycles(8000000);
	distance.limit = 20;
	delay_cycles(8000000);
	distance.limit = 25;
	delay_cycles(8000000);
	distance.limit = 30;
}

void go_straight(float Angle, int length) // 变换角度行走
{
	distance.target = length + distance.real;
	angle.target += wit_to_int16(Angle);
	status = INS;
	distance.limit = 8;    // 阶梯加速防止翘头
	delay_cycles(4000000);
	distance.limit = 14;
	delay_cycles(1000000);
	distance.limit = 21;
	delay_cycles(1000000);
	distance.limit = 28;
	delay_cycles(1000000);
	distance.limit = 36;
	delay_cycles(200000);
	distance.limit = 40;
}

void go_short(float Angle, int length) // 小拐弯
{
	distance.target = length + distance.real;
	angle.target += wit_to_int16(Angle);
	status = INS;
	distance.limit = 10;
	delay_cycles(2000000);
	distance.limit = 20;
}

void start_tarcking() // 开始循迹
{
	set_speed = 8;
	delay_cycles(1000000);
	set_speed = 15;
	delay_cycles(2000000);
	set_speed = 24;
	delay_cycles(3000000);
	set_speed = 30;
	delay_cycles(2000000);
	set_speed = 33;
	status = TARCKING;
}

void start_tarcking_slow() // 开始循迹
{
	set_speed = 8;
	delay_cycles(1000000);
	set_speed = 15;
	delay_cycles(2000000);
	set_speed = 24;
	delay_cycles(3000000);
	set_speed = 28;
	status = TARCKING;
}

void use_task(task *select)
{
	static uint8_t counter = 0;
	switch (*select)
	{
	case QUESTION_1:
		switch (question_status._1)
		{
		case 0: // 起步
			delay_cycles(10000000);
			Bee = 10;
			start_straight();
			question_status._1 = 1;
			break;
		case 1: // 判断停下
			if (distance.real > distance.target - 100)
			{
				status = STOP;
				 Bee = 10;
				question_status._1 = 0;
				*select = NO_QUESTION;
			}
			break;
		}
		break;
	case QUESTION_2:
		switch (question_status._2)
		{
		case 0: // 起步
			delay_cycles(10000000);
			Bee = 10;
			start_straight();
			question_status._2 = 1;
			break;
		case 1:																										 // 惯导
			if (distance.real > distance.target - 100 || (isBlack == true && distance.real > distance.target - 500)) // 判断惯导退出
			{
				Bee = 10;
				rif.target = 2;
				start_tarcking_slow();
				question_status._2 = 2;
			}
			break;
		case 2:													  // 循迹
			if (isBlack == false /*&& angle.target - error > 0*/) // 判断循迹退出
			{
				delay_cycles(10000);
				if (isBlack == true)
					return;
				Bee = 10;
				if (counter == 1) // 退出题目
				{
					status = STOP;
					question_status._2 = 0;
					*select = NO_QUESTION;
					return;
				}
				else
				{
					status = STOP;
					delay_cycles(10000000);
				}
				if (status == STOP)
				{
					go_straight(180, STRAGHT_DISTANCE);
					question_status._2 = 1; // 切换循迹
				}
				counter++;
			}
			break;
		}
		break;
	case QUESTION_3:
		switch (question_status._3)
		{
		case 0: // 起步
			delay_cycles(10000000);
			Bee = 10;
			angle.target = wit_get_yaw(); // 角度矫正
			go_straight(FIRST_TURN, TURN_DISTANCE);
			question_status._3 = 1;
			break;
		case 1:										   // 惯导 (斜走)
			if (distance.real > distance.target - 300) // 判断惯导
			{
				if (isBlack == true) // 遇到黑线
				{
					Bee = 10;
					rif.target = -rif.target;
					start_tarcking();
					question_status._3 = 3;
					tu = ~tu;
				}
				else if (!tu)
				{
					tu = ~tu;
					go_short(-FIRST_TURN - 1.5, SHORT_DISTANCE);
					question_status._3 = 2;
				}
				else
				{
					tu = ~tu;
					go_short(SECOND_TURN + 2, SHORT_DISTANCE + 450);
					question_status._3 = 2;
				}
			}
			break;
		case 2: // 惯导 (直走)
			if (isBlack == true)
			{
				Bee = 10;
				rif.target = -rif.target;
				start_tarcking();
				question_status._3 = 3;
			}
			break;
		case 3: // 循迹
			if (isBlack == false)
			{
				delay_cycles(100);
				if (isBlack == true)
					return;
				Bee = 10;
				if (counter == 1)
				{
					status = STOP;
					question_status._3 = 0;
					*select = NO_QUESTION;
					return;
				}
				else
				{
					status = STOP;
					delay_cycles(500000);
				}
				if (status == STOP)
				{
					angle.target = wit_get_yaw();
					go_straight(-SECOND_TURN, TURN_DISTANCE);
					question_status._3 = 1;
				}
				counter++;
			}
			break;
		}
		break;
	case QUESTION_4:
		switch (question_status._4)
		{
		case 0: // 起步
			delay_cycles(10000000);
			Bee = 10;
			angle.target = wit_get_yaw(); // 角度矫正
			go_straight(FIRST_TURN, TURN_DISTANCE);
			question_status._4 = 1;
			break;
		case 1:										   // 惯导 (斜走)
			if (distance.real > distance.target - 800) // 判断惯导
			{
				if (isBlack == true) // 遇到黑线
				{
					Bee = 10;
					rif.target = -rif.target;
					start_tarcking();
					question_status._4 = 3;
					tu++;
				}
				else if (!tu)
				{
					tu++;
					go_short(-FIRST_TURN - 1.5, SHORT_DISTANCE);
					question_status._4 = 2;
				}
				else
				{
					if (tu % 2 == 1)
					{
						go_short(SECOND_TURN + 2, SHORT_DISTANCE + 450);
						question_status._4 = 2;
					}
					else
					{
						go_short(-SECOND_TURN - 2, SHORT_DISTANCE + 450);
						question_status._4 = 2;
					}
					tu++;
				}
			}
			break;
		case 2: // 惯导 (直走)
			if (isBlack == true)
			{
				Bee = 10;
				rif.target = -rif.target;
				start_tarcking();
				question_status._4 = 3;
			}
			break;
		case 3: // 循迹
			if (isBlack == false)
			{
				delay_cycles(100);
				if (isBlack == true)
					return;
				Bee = 10;
				status = STOP;
				delay_cycles(500000);
				if(tu > 7)
				{
					status = STOP;
					question_status._4 = 0;
					*select = NO_QUESTION;
					return;
				}
				if (tu % 2 == 1)
				{
					angle.target = wit_get_yaw();
					go_straight(-SECOND_TURN, TURN_DISTANCE);
					question_status._4 = 1;
				}
				else
				{
					angle.target = wit_get_yaw();
					go_straight(SECOND_TURN, TURN_DISTANCE);
					question_status._4 = 1;
				}
				counter++;
			}
			break;
		}
		break;
		case QUESTION_5:
		switch (question_status._5)
		{
		case 0: // 起步
			delay_cycles(10000000);
			Bee = 10;
			angle.target = wit_get_yaw(); // 角度矫正
			go_straight(FIRST_TURN, TURN_DISTANCE);
			question_status._5 = 1;
			break;
		case 1:										   // 惯导 (斜走)
			if (distance.real > distance.target - 800) // 判断惯导
			{
				if (isBlack == true) // 遇到黑线
				{
					Bee = 10;
					rif.target = -rif.target;
					start_tarcking();
					question_status._5 = 3;
					tu++;
				}
				else if (!tu)
				{
					tu++;
					go_short(-FIRST_TURN - 1.5, SHORT_DISTANCE);
					question_status._5 = 2;
				}
				else
				{
					if (tu % 2 == 1)
					{
						go_short(SECOND_TURN + 2, SHORT_DISTANCE + 450);
						question_status._5 = 2;
					}
					else
					{
						go_short(-SECOND_TURN - 2, SHORT_DISTANCE + 450);
						question_status._5 = 2;
					}
					tu++;
				}
			}
			break;
		case 2: // 惯导 (直走)
			if (isBlack == true)
			{
				Bee = 10;
				rif.target = -rif.target;
				start_tarcking();
				question_status._5 = 3;
			}
			break;
		case 3: // 循迹
			if (isBlack == false)
			{
				delay_cycles(100);
				if (isBlack == true)
					return;
				Bee = 10;
				status = STOP;
				delay_cycles(500000);
				if (tu % 2 == 1)
				{
					angle.target = wit_get_yaw();
					go_straight(-SECOND_TURN, TURN_DISTANCE);
					question_status._5 = 1;
				}
				else
				{
					angle.target = wit_get_yaw();
					go_straight(SECOND_TURN, TURN_DISTANCE);
					question_status._5 = 1;
				}
				counter++;
				break;
			}
			break;
		}
		break;
	default:
		break;
	}
}
