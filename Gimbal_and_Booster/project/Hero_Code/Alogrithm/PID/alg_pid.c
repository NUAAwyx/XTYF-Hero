#include "alg_pid.h"

void PID_Init(struct PID *pid, float _Kp, float _Ki, float _Kd, float _Kf, float _I_Out_Max, float _Output_Max)
{
    pid->Kp = _Kp;
    pid->Ki = _Ki;
    pid->Kd = _Kd;
    pid->Kf = _Kf;
    pid->I_Out_Max = _I_Out_Max;
    pid->Output_Max = _Output_Max;
    pid->Error = 0;
    pid->Error_Last = 0;
    pid->P_Out = 0;
    pid->I_Out = 0;
    pid->D_Out = 0;
    pid->Output = 0;
}

void PID_Caculate(struct PID *pid)
{
    pid->Error = pid->Target - pid->Now;
    pid->P_Out = pid->Kp * pid->Error;
    pid->I_Out += pid->Ki * pid->Error;
    pid->D_Out = pid->Kd * (pid->Error - pid->Error_Last);
    pid->F_Out = pid->Kf * pid->Target;
    pid->Error_Last = pid->Error;

    if (pid->I_Out > pid->I_Out_Max)
    {
        pid->I_Out = pid->I_Out_Max;
    }
    else if (pid->I_Out < -pid->I_Out_Max)
    {
        pid->I_Out = -pid->I_Out_Max;
    }

    pid->Output = pid->P_Out + pid->I_Out + pid->D_Out + pid->F_Out;

    if (pid->Output > pid->Output_Max)
    {
        pid->Output = pid->Output_Max;
    }
    else if (pid->Output < -pid->Output_Max)
    {
        pid->Output = -pid->Output_Max;
    }
}



void PID_Set_Kp(struct PID *pid, float Kp)
{
    pid->Kp = Kp;
}

void PID_Set_Ki(struct PID *pid, float Ki)
{
    pid->Ki = Ki;
}

void PID_Set_Kd(struct PID *pid, float Kd)
{
    pid->Kd = Kd;
}

void PID_Set_Kf(struct PID *pid, float Kf)
{
    pid->Kf = Kf;
}

void PID_Set_Target(struct PID *pid, float target)
{
    pid->Target = target;
}

void PID_Set_Now(struct PID *pid, float now)
{
    pid->Now = now;
}

float PID_Get_Output(struct PID *pid)
{
    return pid->Output;
}

