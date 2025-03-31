#ifndef __ALG_PID_H
#define __ALG_PID_H

struct PID
{
    float Kp;
    float Ki;
    float Kd;
    float Kf;
    float Error;
    float Error_Last;
    float P_Out;
    float I_Out;
    float D_Out;
    float F_Out;
    float Output;
    float I_Out_Max;
    float Output_Max;

    float Target;
    float Now;
};

void PID_Init(struct PID *pid, float _Kp, float _Ki, float _Kd, float _Kf, float _I_Out_Max, float _Output_Max);

void PID_Caculate(struct PID *pid);

void PID_Set_Kp(struct PID *pid, float Kp);

void PID_Set_Ki(struct PID *pid, float Ki);

void PID_Set_Kd(struct PID *pid, float Kd);

void PID_Set_Kf(struct PID *pid, float Kf);

void PID_Set_Now(struct PID *pid, float Now);

void PID_Set_Target(struct PID *pid, float Target);

float PID_Get_Output(struct PID *pid);




#endif