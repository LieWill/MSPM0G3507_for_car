#ifndef __TASK_H__
#define __TASK_H__

typedef enum {
		NO_QUESTION = 0,
    QUESTION_1 = 1,
    QUESTION_2 = 2,
    QUESTION_3 = 3,
    QUESTION_4 = 4,
    QUESTION_5 = 5
} task;

void use_task(task *select);

#endif // !__TASK_H__
