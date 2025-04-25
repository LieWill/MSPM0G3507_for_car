#include "task.h"
#include "pid.h"
#include "ti_msp_dl_config.h"
#include "rif.h"

#define STRAGHT_DISTANCE  1000
#define TURN_DISTANCE 1400 

//enum
//{
//    BEGIN,    // 开始
//    STRAIGHT, // 直走
//    TURN,     // 转
//    TARCKING, // 循迹
//    END,      // 停
//} status = BEGIN;

//extern pid_distance distance;

//int length = 0;
//bool finish = false;

void use_task(task select)
{
//    static uint8_t counter = 0;
//    switch (select)
//    {
//    case QUESTION_1:
//        if (status == BEGIN)
//        {
//            length = STRAGHT_DISTANCE;
//            status = STRAIGHT;
//        }
//        else if (status == STRAIGHT)
//        {
//            if (distance.real > STRAGHT_DISTANCE - 100)
//                status = END;
//        }
//        break;
//    case QUESTION_2:
//        if (status == BEGIN)
//        {
//            length = distance.real + STRAGHT_DISTANCE;
//            status = STRAIGHT;
//        }
//        else if (status == STRAIGHT)
//        {
//            if (distance.real > STRAGHT_DISTANCE - 100)
//            {
//                if(counter > 2)
//                    status = END;
//                else
//                    status = TARCKING;
//                counter++;
//            }
//        }
//        else if(status == TARCKING && rif_getValue() == 0)
//        {
//            length = distance.real + STRAGHT_DISTANCE;
//            status = STRAIGHT;
//            counter++;
//        }
//        break;
//    case QUESTION_3:
//        break;
//    case QUESTION_4:
//        break;
//    default:
//        break;
//    }
}
