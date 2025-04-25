#ifndef __TASK_H__
#define __TASK_H__

typedef enum {
    QUESTION_1,
    QUESTION_2,
    QUESTION_3,
    QUESTION_4,
    NO_QUESTION
} task;

void use_task(task select);

#endif // !__TASK_H__
