#include <stdio.h>
#include <math.h>
#define pi 3.14159265358979323846

//���������� ����������
int fact(int k)
{
    int f = 1, i;
    for (i = 2; i <= k; i++)
        f = f * i;
    return f;
}



double mysin(double x, double ep)
{
    double S = 0, S_1; // S - ����� ����, S_1 - ���������� �������� ����� ����
    int zn = 1, n = 1, sign = 1; // sign - ��� �������� �������� 

    // ��� x < 0 ���� � ������������� ����� ������
    if (x < 0)
    {
        sign = -1;     //������ ���� �� �����
        x = fabs(x);  //���� ������ �� ������
    }

    //���� ���� ������ 2��, �� ��� � ������� �� 0 �� 2�� 
    x = fmod(x, 2 * pi);//����� ���� �� 2��, ������� ������� �� �������

    //���� x ������ ��, �� ���� � ������� �� 0 �� ��
    if (x > pi)
    {
        x = x - pi; 
        sign = sign * (-1); // ������ ���� �� ���������������. (���� ��� -, ����� +) 
    }

    //x > (pi/2) peremeshtaem v interval [0..pi/2]
    if (x > (pi / 2))
        x = pi - x; // ������: ���� �� �� ������� 3/4�� ������� ������ ���� ��/4 (�����(3/4��) = �����(��/4)) 

    do
    {
        S_1 = S;
        S = S + (zn * pow(x, 2 * n - 1) / fact(2 * n - 1));
        n = n + 1;
        zn = zn * (-1);
    } while (fabs(S - S_1) > ep); //�������� � ����� �� ��� ��� ���� ����������� �������
    S = S * sign;
    return S;
}
double mycos(double x, double ep)
{
    double S = 0, S_1;
    int zn = 1, n = 1, sign = 1;

    //���� � ������ 0, ����� �� ������
    if (x < 0) x = fabs(x);
    //ecli x>2Pi peremeshtaem v interval [0..2pi]
    x = fmod(x, 2 * pi);//ostatok ot deleniya x/(2*pi) , ubiraem period

    //x > pi peremeshtaem v interval [0..pi]
    if (x > pi)
    {
        x = 2 * pi - x; // ����� �������� ���� �� 0 �� ��, �������� �� 2�� ��������� ���� >�� 
    }

    //x > (pi/2) peremeshtaem v interval [0..pi/2]
    if (x > (pi / 2))
    {
        x = pi - x;
        sign = sign * (-1); //�.� �� 0 �� ��/2 ���� + � �� ��/2 �� �� ���� -, �� ������ ���� 
    }

    do
    {
        S_1 = S; //predydushee znachenie summy
        S = S + (zn * pow(x, 2 * n - 2) / fact(2 * n - 2));
        n = n + 1;
        zn = zn * (-1);
    } while (fabs(S - S_1) > ep);
    S = S * sign;
    return S;
}
double mytan(double x, double ep) //���� ������� �� ������� ���� �������
{
    double s, c; // s -�����, c - �������

    s = mysin(x, ep); //��� � ������� ������
    c = mycos(x, ep); //��� � ������� ��������
    return(s/c);

}
int main(void)
{
    double ep = 0.000001;
    double g; // ��� �������� ����

    for (g = -2 *pi; g  <= 2 * pi; g = g + pi / 10.) // � ����� 1/10 pi ��� �� 6pi �� ���� (���������� ������ ����, ����� ��������� �������)
    {
        if (fabs(fmod(fabs(g), pi) - pi / 2)>=ep) //��� ����� pi/2 ���� �������� �������
        {
            printf("mytg(%8.5f) = %9.6f  tg(%8.5f) =%9.6f\n", g, mytan(g, ep),g, tan(g)); // ������ ���� ���. ����� � �������� ��������� � ������ ��������
        }
        else
        {
             printf("no result\n"); // ������� ����� ������� ������ EP
        }

    }
    return 0;


}