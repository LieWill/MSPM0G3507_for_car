#include "task.h"
#include "pid.h"
#include "ti_msp_dl_config.h"
#include "rif.h"
#include "wit.h"
#include "OLED.h"

#define STRAGHT_DISTANCE 3300
#define TURN_DISTANCE 4000

enum
{
    BEGIN,    // 开始
    STRAIGHT, // 直走
    TURN,     // 转
    TARCKING, // 循迹
    END,      // 停
} status = BEGIN;
extern float set_speed;

extern pid_wit angle;

extern pid_distance distance;

extern bool isBlack;
	
void start_straight()
{
	distance.target = STRAGHT_DISTANCE + distance.real;
	angle.target = wit_get_yaw();
	status = TURN;
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

void go_straight(float Angle, int length)
{
	distance.target = length + distance.real;
	angle.target += wit_to_int16(Angle);
	status = TURN;
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

void tarcking()
{
	status = TARCKING;
	set_speed = 5;
	delay_cycles(8000000);
	set_speed = 10;
	delay_cycles(8000000);
	set_speed = 25;
	if(status == TARCKING)
		OLED_ShowString(2, 1, "TA");
	else
		OLED_ShowString(2, 1, "TU");
	while((GPIOB->DIN31_0 & 0xFFF) != 0);
	delay_cycles(10000);
	status = END;
}

void question2()
{
	OLED_ShowString(4, 1, "S1");
	start_straight();
	OLED_ShowString(4, 1, "T1");
	tarcking();
	//status = END;
	OLED_ShowString(4, 1, "S2");
	start_straight();
	OLED_ShowString(4, 1, "T2");
	tarcking();
	OLED_ShowString(4, 1, "ED");
}

bool finish = false;

void use_task(task *select)
{
    static uint8_t counter = 0;
    switch (*select)
    {
    case QUESTION_1:
        if (status == BEGIN)
        {
					delay_cycles(10000000);
					start_straight();
        }
        else if (status == TURN)
        {
          if (distance.real > distance.target - 100 || isBlack == true)
					{
						status = END;
					}
        }
				else if(status == END)
				{
					status = BEGIN;
					*select = NO_QUESTION;
				}
        break;
    case QUESTION_2:
        if (status == BEGIN)
        {
					delay_cycles(10000000);
					start_straight();
        }
        else if (status == TURN)
        {
            if (distance.real > distance.target - 100 || (isBlack == true && distance.real > distance.target - 300))
						{
								set_speed = 32;
								status = TARCKING;
						}
        }
				else if(status == TARCKING)
				{
					//int16_t error = wit_get_yaw() + wit_to_int16(160);
					if(isBlack == false /*&& angle.target - error > 0*/)
					{
						delay_cycles(10000);
						if((GPIOB->DIN31_0 & 0xFFF) != 0)
							return;
						if(counter > 0)
						{
							status = END;
							return;
						}
						else
						{
							status = END;
							delay_cycles(20000000);
						}
						if(status == END)
						{
							go_straight(180, STRAGHT_DISTANCE);
							status = TURN;
						}
						counter++;
					}
				}
				else if(status == END)
				{
					*select = NO_QUESTION;
					status = BEGIN;
				}
        break;
    case QUESTION_3:
				if (status == BEGIN)
        {
					delay_cycles(10000000);
					angle.target = wit_get_yaw();
					go_straight(38 , TURN_DISTANCE);
        }
        else if (status == TURN)
        {
            if (distance.real > distance.target - 100 || (isBlack == true && distance.real > distance.target - 300))
						{
								set_speed = 32;
								status = TARCKING;
						}
        }
				else if(status == TARCKING)
				{
					if(isBlack == false)
					{
						delay_cycles(10000);
						if((GPIOB->DIN31_0 & 0xFFF) != 0)
							return;
						if(counter > 0)
						{
							status = END;
							return;
						}
						else
						{
							status = END;
							delay_cycles(20000000);
						}
						if(status == END)
						{
							angle.target = wit_get_yaw();
							go_straight(-54, TURN_DISTANCE);
							status = TURN;
						}
						counter++;
					}
				}
				else if(status == END)
				{
					*select = NO_QUESTION;
					status = BEGIN;
				}
        break;
    case QUESTION_4:
        angle.target = wit_get_yaw();
				distance.limit = 20;
				go_straight(39, 0);
				*select = NO_QUESTION;
        break;
    default:
        break;
    }
}
