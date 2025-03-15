#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_RECORDS 50
#define MAX_STRING 20
// �������ݽṹ
typedef struct car
{
    char carID[MAX_STRING];
    char brand[MAX_STRING];
    char model[MAX_STRING];
    int type;
    int age;
    float mileage;
    int condition;
    int accident;
    float prepCost;
    float newCarPrice;
    float estimatedPrice;
} Car;

// ������¼���ݽṹ
typedef struct sale
{
    char carID[MAX_STRING];
    int action;
    char date[MAX_STRING];
    float cost;
    char memberID[MAX_STRING];
    char employeeID[MAX_STRING];
} SaleRecord;

// ȫ����������
int f=0;
Car carData[MAX_RECORDS];//��ʱ�������ݣ�����������һ��
SaleRecord saleData[MAX_RECORDS];
int carCount = 0//�������ж���̨
               , saleCount = 0;//sale�ж�������Ϣ


// ��������
//�������������������Ұ����������������0.0
// ���س�������
void loadCarData()
{
    FILE *file = fopen("cardata.txt", "r");//ֻ��
    if (file==NULL)
    {
        printf("�޷����ļ� cardata.txt\n");//³����
        return 0;
    }

    while (fscanf(file, "%s %s %s %d %d %f %d %d %f %f %f",
                  carData[carCount].carID,
                  carData[carCount].brand,
                  carData[carCount].model,
                  &carData[carCount].type,
                  &carData[carCount].age,
                  &carData[carCount].mileage,
                  &carData[carCount].condition,
                  &carData[carCount].accident,
                  &carData[carCount].prepCost,
                  &carData[carCount].newCarPrice,
                  &carData[carCount].estimatedPrice) == 11)//ͬʱ���벢�ж���û�е���
    {
        carCount++;//��¼����
    }

    fclose(file);
}

// ���ز�����¼���ݣ�ͬ��
void loadSaleData()
{
    FILE *file = fopen("./saledata.txt", "r");
    if (!file)
    {
        printf("�޷����ļ�saledata.txt\n");
        exit(1);
    }

    while (fscanf(file, "%s %d %s %f %s %s",
                  saleData[saleCount].carID,
                  &saleData[saleCount].action,
                  saleData[saleCount].date,
                  &saleData[saleCount].cost,
                  saleData[saleCount].memberID,
                  saleData[saleCount].employeeID) == 6)
    {
        saleCount++;
    }
    fclose(file);

}
//���ɹ���
void press()
{
    char a;
    printf("���س����Է������˵�...");
    while (getchar() != '\n');  // ��ջ������е������ַ�
    scanf("%c", &a);            // �ȴ����з�
    mainscreen();
}
#define ADMIN_PASSWORD "admin123"
// ����Ա����
int check_admin_password()
{
    char password[MAX_STRING];
    printf("���������Ա����: ");
    scanf("%s", password);
    return strcmp(password, ADMIN_PASSWORD) == 0;//����ǲ��ǵĽ���������ж�
}
//��ҳ��
int mainscreen()
{
    int choice,flag=0;//flag�ж��Ƿ�Ҫ�ٽ���ҳ��
    while (1)
    {
        printf("       ______               ______\n"        );
        printf("      /|_||_\\`.__         /|_||_\\`.__\n"   );
        printf("     (   _    _ _\\       (   _    _ _\\\n"  );
        printf("     =`-(_)--(_)-'        =`-(_)--(_)-'\n"   );
        printf("======== ���ֳ�����ϵͳ ========\n");
        printf("1. ��ѯ\n");
        printf("2. ����\n");
        printf("3. �������\n");
        printf("4. �޸�����\n");
        printf("5. ��������\n");
        printf("6. ͳ������\n");
        printf("7. �������ݲ��˳�\n");
        printf("0. �˳�ϵͳ\n");
        printf("==========================\n");
        printf("��ѡ���ܣ��������֣���");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("\n\n");
            search();
            break;
        case 2:
            printf("\n\n");
            sort();
            break;
        case 3:
            printf("\n\n");
            output();
            break;
        case 4:
            printf("\n\n");
            revise();
            break;
        case 5:
            printf("\n\n");
            new_data();
            break;

        case 6:
            printf("\n\n");
            counting();
            break;

        case 7:
            printf("\n\n");
            data_keep();
            break;
        case 0:
            printf("�Ƿ񱣴���ģ���1-��/2-��");//��ʾ�������
            int z=0;
            scanf("%d",&z);
            if(z==1)
            {
                f=1;
                data_keep();
                break;
            }

            else
            {
                printf("�˳�ϵͳ��...\n");
                return 0;
            }
        default:
            printf("��Ч���룬������ѡ��\n");
            flag=1;
            break;
        }
        if(flag==1)
            continue;
        else
            break;
    }

}
//���ҹ��ܲ˵�
void search()
{
    int a;
    printf("======== ��ѯ���� ========\n");
    printf("1. ����̺ͳ���\n");
    printf("2. ָ��Ա���Ĳ�����¼\n");
    printf("3. ���³��ۺ�Ԥ����\n");
    printf("4. ���Ƿ����¹�\n");
    printf("5. ����Ա�Ų�ѯ\n");
    printf("0. �˳�����ҳ��\n");
    printf("==========================\n");
    printf("��ѡ���ܣ��������֣���");
    scanf("%d", &a);
    switch(a)
    {
    case 1:
        queryCarsByMileageAndCondition();//����1
        break;
    case 2:
        queryEmployeeRecords();//����2
        break;
    case 3:
        queryNewPre();//����3
        break;
    case 4:
        queryAnci();//����4
        break;
    case 5:
        vip();
        break;
    default:
        printf("������������ԣ�");
        search();
        break;
    case 0://�˳�
        mainscreen();
        break;
    }
    press();
}
// ��ѯָ��������ںͳ����ĳ���
void queryCarsByMileageAndCondition()
{
    float maxMileage;
    int minCondition;
    //������������
    printf("�����������̣���λ�����ʾ����10.0����");
    scanf("%f", &maxMileage);
    printf("��������ͳ�����1��10��ʾ����8����");
    scanf("%d", &minCondition);

    printf("���������ĳ������£�\n");
    printf("�������\tƷ��\t\t�ͺ�\t���\t����\tԤ���ۼ�\n");
    for (int i = 0; i < carCount; i++)
    {
        if (carData[i].mileage <= maxMileage && carData[i].condition >= minCondition)
        {
            printf("%s\t\t%s\t\t%s\t%.1f\t%d\t%.1f\n",
                   carData[i].carID,
                   carData[i].brand,
                   carData[i].model,
                   carData[i].mileage,
                   carData[i].condition,
                   carData[i].estimatedPrice);
        }
    }

}

// ��ѯָ��Ա�������в�����¼
void queryEmployeeRecords()
{
    char employeeID[MAX_STRING];
    printf("������Ա�����ţ�ʾ����E001����");
    scanf("%s", employeeID);//��������
    printf("��Ա���Ĳ�����¼���£�\n");
    printf("�������\t��������\t����\t\t��������\n");
    for (int i = 0; i < saleCount; i++)
    {
        if (strcmp(saleData[i].employeeID, employeeID) == 0)
        {
            printf("%s\t\t%d\t\t%5s\t%f\n",
                   saleData[i].carID,
                   saleData[i].action,
                   saleData[i].date,
                   saleData[i].cost);
        }
    }
}
void vip()
{
    char vipID[MAX_STRING];
    printf("�������Ա�ţ�ʾ����M001����");
    scanf("%s", vipID);//��������
    printf("�û�Ա�Ĳ�����¼���£�\n");
    printf("�������\t��������\t����\t\t��������\n");
    for (int i = 0; i < saleCount; i++)
    {
        if (strcmp(saleData[i].memberID, vipID) == 0)
        {
            printf("%s\t\t%d\t\t%5s\t%f\n",
                   saleData[i].carID,
                   saleData[i].action,
                   saleData[i].date,
                   saleData[i].cost);
        }
    }
}
//��ѯ�³��ۺ�Ԥ����
void queryNewPre()
{
    float maxNew;
    int minPre;
//��������
    printf("����������³���λ��(���֣�");
    scanf("%f", &maxNew);
    printf("���������Ԥ���λ�������֣�");
    scanf("%d", &minPre);

    printf("���������ĳ������£�\n");
    printf("�������\tƷ��\t\t�ͺ�\t���\t����\tԤ���ۼ�\n");
    for (int i = 0; i < carCount; i++)
    {
        if (carData[i].newCarPrice <= maxNew && carData[i].estimatedPrice >= minPre)
        {
            printf("%s\t\t%s\t\t%s\t%.1f\t%d\t%.1f\n",
                   carData[i].carID,
                   carData[i].brand,
                   carData[i].model,
                   carData[i].mileage,
                   carData[i].condition,
                   carData[i].estimatedPrice);
        }
    }

}
//���Ƿ����¹ʲ�ѯ
void queryAnci()
{

    int a;
    printf("������������󣺣�1-��/0-��");
    scanf("%f", &a);
    printf("���������ĳ������£�\n");
    printf("�������\tƷ��\t\t�ͺ�\t���\t����\tԤ���ۼ�\n");
    for (int i = 0; i < carCount; i++)
    {
        if (carData[i].accident== a)
        {
            printf("%s\t\t%s\t\t%s\t%.1f\t%d\t%.1f\n",
                   carData[i].carID,
                   carData[i].brand,
                   carData[i].model,
                   carData[i].mileage,
                   carData[i].condition,
                   carData[i].estimatedPrice);
        }
    }
}
//�����ܲ˵�
void sort()
{
    int a;
    printf("======== ������ ========\n");
    printf("1. ���۳���Ʒ�ƽ�������\n");
    printf("2. ���۳���Ԥ�������۽�������\n");
    printf("3. ���������������\n");
    printf("4. ��ά�޼۽�������\n");
    printf("0. �˳������˵�\n");
    printf("==========================\n");
    printf("��ѡ���ܣ��������֣���");
    scanf("%d", &a);
    switch(a)
    {
    case 1:
        printf("\n\n");
        sort_brand();//����1
        break;
    case 2:
        printf("\n\n");
        sort_predict();//����2
        break;
    case 3:
        printf("\n\n");
        sort_mileage();//����3
        break;
    case 4:
        printf("\n\n");//����4
        sort_p();
        break;
    default:
        printf("������������ԣ�");
        sort();
        break;
    case 0:
        mainscreen();
        break;
    }
    press();
}
// ��Ʒ������ð������
void sort_brand()
{
    for (int i=0; i<carCount-1; i++)
    {
        for (int j=0; j<carCount-1-i; j++)
        {
            if (strcmp(carData[j].brand, carData[j + 1].brand)>0)
            {
                // ����������¼
                Car temp;
                temp=carData[j];
                carData[j]=carData[j + 1];
                carData[j + 1]=temp;
            }
        }
    }
    printf("�������\tƷ��\t\t�ͺ�\t\t����\t����\t���\t����\t�¹�\t��������\t�³�����\tԤ���ۼ�\n");
    for (int i=0; i <carCount; i++)
    {
        printf("%s\t\t%s\t\t%s\t\t%d\t%d\t%.2f\t%d\t%d\t%.1f\t\t%.1f\t\t%.1f\n",
               carData[i].carID,
               carData[i].brand,
               carData[i].model,
               carData[i].type,
               carData[i].age,
               carData[i].mileage,
               carData[i].condition,
               carData[i].accident,
               carData[i].prepCost,
               carData[i].newCarPrice,
               carData[i].estimatedPrice);
    }
}
//��Ԥ��۸�����
void sort_predict()
{
    for (int i=0; i<carCount-1; i++)
    {
        for (int j=0; j<carCount-1-i; j++)
        {
            if (carData[j].estimatedPrice>carData[j+1].estimatedPrice)
            {
                // ����������¼
                Car temp;
                temp=carData[j];
                carData[j] = carData[j+1];
                carData[j+1]=temp;
            }
        }
    }
    printf("�������\tƷ��\t\t�ͺ�\t\t����\t����\t���\t����\t�¹�\t��������\t�³�����\tԤ���ۼ�\n");
    for (int i=0; i<carCount; i++)
    {
        printf("%s\t\t%s\t\t%s\t\t%d\t%d\t%.1f\t%d\t%d\t%.1f\t\t%.1f\t\t%.1f\n",
               carData[i].carID,
               carData[i].brand,
               carData[i].model,
               carData[i].type,
               carData[i].age,
               carData[i].mileage,
               carData[i].condition,
               carData[i].accident,
               carData[i].prepCost,
               carData[i].newCarPrice,
               carData[i].estimatedPrice);
    }
}
//�����������
void sort_mileage()
{
    for (int i=0; i<carCount-1; i++)
    {
        for (int j=0; j<carCount-1-i; j++)
        {
            if (carData[j].mileage>carData[j+1].mileage)
            {
                // ����������¼
                Car temp;
                temp= carData[j];
                carData[j] = carData[j+1];
                carData[j+1] = temp;
            }
        }
    }
    printf("�������\tƷ��\t�ͺ�\t\t\t����\t����\t���\t����\t�¹�\t��������\t�³�����\tԤ���ۼ�\n");
    for (int i=0; i<carCount; i++)
    {
        printf("%s\t\t%s\t%s\t\t\t%d\t%d\t%.2f\t%d\t%d\t%.1f\t\t%.1f\t\t%.1f\n",
               carData[i].carID,
               carData[i].brand,
               carData[i].model,
               carData[i].type,
               carData[i].age,
               carData[i].mileage,
               carData[i].condition,
               carData[i].accident,
               carData[i].prepCost,
               carData[i].newCarPrice,
               carData[i].estimatedPrice);
    }
}
//��ά�޷�����
void sort_p()
{
    for (int i=0; i<carCount-1; i++)
    {
        for (int j=0; j<carCount-1-i; j++)
        {
            if (carData[j].prepCost>carData[j+1].prepCost)
            {
                // ����������¼
                Car temp;
                temp=carData[j];
                carData[j]=carData[j+1];
                carData[j+1]=temp;
            }
        }
    }
    printf("�������\tƷ��\t�ͺ�\t\t\t����\t����\t���\t����\t�¹�\t��������\t�³�����\tԤ���ۼ�\n");
    for (int i=0; i<carCount; i++)
    {
        printf("%s\t\t%s\t%s\t\t\t%d\t%d\t%.2f\t%d\t%d\t%.1f\t\t%.1f\t\t%.1f\n",
               carData[i].carID,
               carData[i].brand,
               carData[i].model,
               carData[i].type,
               carData[i].age,
               carData[i].mileage,
               carData[i].condition,
               carData[i].accident,
               carData[i].prepCost,
               carData[i].newCarPrice,
               carData[i].estimatedPrice);
    }
}
//�����ҳ��
void output()
{
    int a;
    printf("======== ��� ========\n");
    printf("1. ���������Ϣ\n");
    printf("2. ������ۼ�¼\n");
    printf("3. �˳�����ҳ��\n");
    printf("==========================\n");
    printf("��ѡ���ܣ��������֣���");
    scanf("%d", &a);
    switch(a)
    {
    case 1:
        printf("\n\n");
        output_car();
        break;
    case 2:
        printf("\n\n");
        output_sale();
        break;
    case 3:
        printf("\n\n");
        mainscreen();
        break;
    default:
        printf("������������ԣ�");
        output();
        break;
    }
    press();
}
//���cardata.txt**������
void output_car()
{
    int count=0,flag=1,i=0;
    for(i=0; i<carCount; i++)
    {
        if(count==0)
        {
            printf("���\tƷ��\t\t�ͺ�\t\t����\t����\t����\t�¹�\t���\t��������\t�³��۸�\tԤ���ۼ�\n");
        }
        {
            printf("%s\t%s\t\t%s\t\t%d\t%d\t%d\t%d\t%.1f\t%.1f\t\t%.1f\t\t%.1f\n",
                   carData[i].carID,
                   carData[i].brand,
                   carData[i].model,
                   carData[i].type,
                   carData[i].age,
                   carData[i].condition,
                   carData[i].accident,
                   carData[i].mileage,
                   carData[i].prepCost,
                   carData[i].newCarPrice,
                   carData[i].estimatedPrice);
            count++;
            if(count%10==0)
            {
                printf("**��ǰΪ��%dҳ����%dҳ����1����һҳ����2��һҳ...**",flag,carCount/10+1);
                int a;
                scanf("%d", &a); // �ȴ�ָ��
                if(a==1)
                {
                    if(i==10)//��Ϊ��һҳʱ���޷���һҳ
                        i-=10;
                    else//��Ϊ��һҳʱ
                        i-=20;
                    count-=10;
                    if(flag!=1)
                        flag--;
                }
                else
                {
                    count+=10;
                    if(flag!=3)
                        flag++;
                }

            }
        }
    }
}
//������ۼ�¼
void output_sale()
{
    int count=0,flag=1,i=0;
    for(i=0; i<saleCount; i++)
    {
        if(count==0)
        {
            printf("���\t����\t����\t��������\t�û���Ա��\tԱ������\n");
        }

        printf("%s\t%d\t%d\t%.1f\t\t%s\t\t%s\n",
               saleData[i].carID,
               saleData[i].action,
               saleData[i].date,
               saleData[i].cost,
               saleData[i].memberID,
               saleData[i].employeeID);
        count++;
        if(count%10==0)
        {
            printf("**��ǰΪ��%dҳ����%dҳ����1����һҳ����2��һҳ...**",flag,saleCount/10+1);
            int a;
            scanf("%d", &a); // �ȴ�ָ��
            if(a==1)
            {
                if(i==10)//��Ϊ��һҳʱ���޷���һҳ
                    i-=10;
                else//��Ϊ��һҳʱ
                    i-=20;
                count-=10;
                if(flag!=1)
                    flag--;
            }
            else
            {
                count+=10;
                if(flag!=3)
                    flag++;
            }

        }

    }
}

//�޸ļ�¼��������
void revise()
{
    int a;
    if(check_admin_password()==0)
    {
        printf("��������޷�ִ���޸Ĳ�����");
        fflush(stdin);
        mainscreen();
    }
    printf("��¼�ɹ���\n");
    printf("======== �޸� ========\n");
    printf("1. �޸����ۼ�¼�еĶԽӹ���\n");
    printf("2. �޸�Ԥ������\n");
    printf("3. �޸ĳ��������Ϣ\n");
    printf("0. �˳�����ҳ��\n");
    printf("==========================\n");
    printf("��ѡ���ܣ��������֣���");
    scanf("%d", &a);
    switch(a)
    {
    case 1:
        printf("\n\n");
        revise_emp();
        break;
    case 2:
        printf("\n\n");
        revise_precost();
        break;
    case 3:
        printf("\n\n");
        revise_car();
        break;
    case 0:
        printf("\n\n");
        mainscreen();
        break;
    default:
        printf("���޶�Ӧѡ������ԣ�");
        revise();
        break;
    }

}
//�޸ĶԽӹ���
void revise_emp()
{
    int flag=0;
    char a[20];
    char b[20];
    int i;
    printf("�����복����ţ�ʾ����C001����");
    scanf("%s",a);
    for (i=0,flag=0; i<saleCount; i++)
    {
        if (strcmp(saleData[i].carID,a)==0)
        {
            printf("�޸�Ϊ��");
            scanf("%s",b);
            strcpy(saleData[i].employeeID,b);
            flag=1;
            break;
        }

    }
    if(flag==1)
        printf("�޸ĳɹ���\n");
    else if(flag==0)
    {
        printf("�������");
        revise_emp();
    }
    data_keep();
    press();
}
//�޸�ԤԼ�۸�
void revise_precost()
{
    int flag=0;
    char a[20];
    float b;
    int i;
    printf("�����복����ţ�ʾ����C001����");
    scanf("%s",&a);
    fflush(stdin);
    for (i=0,flag=0; i<saleCount; i++)
    {
        if (saleData[i].action==2&&strcmp(saleData[i].carID,a)==0)
        {
            printf("�޸�Ϊ��");
            scanf("%f",&b);
            saleData[i].cost=b;
            flag=1;
            break;

        }
    }
    if(flag==1)
    printf("�޸ĳɹ���");
    else if(flag==0&&saleData[i].action!=2)
    {
        printf("������û�б�ԤԼ��");
    }
    else if(flag==0)
    {
       printf("�������");
     revise_emp();
    }
    data_keep();
    press();
}
//�޸ĳ�����Ϣ����ź��ͺŲ����޸ģ�
void revise_car()
{
    char car_id[MAX_STRING];
    printf("������Ҫ�޸ĵĳ����ı�ţ���ʾ��C001)");
    scanf("%s",car_id);
    int flag=0,i;
    for(i=0; i<carCount; i++)
    {
        if(strcmp(car_id,carData[i].carID)==0)
        {
            printf("������Ʒ�ƣ���Ʒ������");
            scanf("%s", carData[i].brand);
            printf("�������ͺţ����ͺţ�");
            scanf("%d", &carData[i].model);
            printf("�����복�䣺(���֣�");
            scanf("%d", &carData[i].age);
            printf("��������̣���λ�������");
            scanf("%f", &carData[i].mileage);
            printf("�����복����1-10����");
            scanf("%d", &carData[i].condition);
            printf("�������Ƿ������¹ʣ�0-�ޣ�1-�У���");
            scanf("%d", &carData[i].accident);
            printf("�������������ã�");
            scanf("%f", &carData[i].prepCost);
            printf("�������³����ۣ�");
            scanf("%f", &carData[i].newCarPrice);
            printf("������Ԥ���ۼۣ�");
            scanf("%f", &carData[i].estimatedPrice);
            flag=1;
        }
    }
    if(flag==0)
    {
        printf("�ñ�Ų����ڣ������ԡ�");
        revise_car();
    }
    else
    {
        printf("�޸ĳɹ���");
        press();
        data_keep();
    }
}

//ͳ����ҳ��
void counting()
{
    int a;
    printf("======== ͳ�� ========\n");
    printf("1. ��˾ӯ��״̬\n");
    printf("2. ��ǰ���۹ھ�\n");
    printf("3. ���ܻ�ӭ�ĳ���Ʒ��\n");
    printf("4. ��ܻ�ӭ�ĳ���Ʒ��\n");
    printf("0. �˳�����ҳ��\n");
    printf("==========================\n");
    printf("��ѡ���ܣ��������֣���");
    scanf("%d", &a);
    switch(a)
    {
    case 1:
        printf("\n\n");
        money();
        break;
    case 2:
        printf("\n\n");
        sale_champion();
        break;
    case 3:
        printf("\n\n");
        pop_brand();
        break;
    case 4:
        printf("\n\n");
        worst_brand();
        break;
    case 0:
        printf("\n\n");
        mainscreen();
        break;
    default:
        printf("�������������");
        counting();
        break;
    }
}
//ͳ�ƹ�˾ӯ��
void money()
{
    int i,j;
    float sum=0;
    for(i=0; i<saleCount; i++)
    {
        switch(saleData[i].action)
        {
        case 1:
            sum-=saleData[i].cost;
            break;
        case 2:
            sum+=saleData[i].cost;
            break;
        case 3:
            sum-=saleData[i].cost;
            break;
        case 4:
            sum+=saleData[i].cost;
            break;
        }
    }
    printf("��ǰ��˾��ӯ��Ϊ��%.1f��Ԫ\n",sum);
    press();
}
//ͳ��˭������(�����¼��ࣩ**������
void sale_champion()
{
    int maxCount = 0;
    char champion[MAX_STRING];

    // ͳ��ÿ��Ա�����������¼�Ĵ���
    for (int i = 0; i < saleCount; i++)
    {
        int count = 0;
        for (int j = 0; j < saleCount; j++)
        {
            if (strcmp(saleData[i].employeeID, saleData[j].employeeID) == 0)
            {
                count++;
            }
        }
        if (count > maxCount)
        {
            maxCount = count;
            strcpy(champion, saleData[i].employeeID);
        }
    }

    // �������
    printf("���۹ھ�Ϊ��Ա������ %s�����������%d\n", champion, maxCount);
    press();
}

//���ܻ�ӭ������Ʒ��
void pop_brand()
{
    int brandCount[MAX_RECORDS] = {0};
    char brands[MAX_RECORDS][MAX_STRING];

    int brandIndex = 0;
    for (int i = 0; i < carCount; i++)
    {
        int found = 0;
        for (int j = 0; j < brandIndex; j++)
        {
            if (strcmp(carData[i].brand, brands[j]) == 0)
            {
                brandCount[j]++;
                found = 1;
                break;
            }
        }
        if (!found)
        {
            strcpy(brands[brandIndex], carData[i].brand);
            brandCount[brandIndex] = 1;
            brandIndex++;
        }
    }

    int maxCount = 0;
    for (int i = 0; i < brandIndex; i++)
    {
        if (brandCount[i] > maxCount)
        {
            maxCount = brandCount[i];
        }
    }

    printf("���ܻ�ӭ��Ʒ�ƣ�\n");
    for (int i = 0; i < brandIndex; i++)
    {
        if (brandCount[i] == maxCount)
        {
            printf("%s\n", brands[i]);
        }
    }
    press();
}
//��ܻ�ӭ��Ʒ��
void worst_brand()
{
    int brandCount[MAX_RECORDS] = {0};
    char brands[MAX_RECORDS][MAX_STRING];

    int brandIndex = 0;
    for (int i = 0; i < carCount; i++)
    {
        int found = 0;
        for (int j = 0; j < brandIndex; j++)
        {
            if (strcmp(carData[i].brand, brands[j]) == 0)
            {
                brandCount[j]++;
                found = 1;
                break;
            }
        }
        if (!found)
        {
            strcpy(brands[brandIndex], carData[i].brand);
            brandCount[brandIndex] = 1;
            brandIndex++;
        }
    }

    int minCount = 100;
    for (int i = 0; i < brandIndex; i++)
    {
        if (brandCount[i] < minCount)
        {
            minCount = brandCount[i];
        }
    }

    printf("��ܻ�ӭ��Ʒ�ƣ�\n");
    for (int i = 0; i < brandIndex; i++)
    {
        if (brandCount[i] == minCount)
        {
            printf("%s\n", brands[i]);
        }
    }
    press();
}
//��������
void new_data()
{
    int flag=0;
    int choice;
    if(flag==0)
        if(check_admin_password()==0)
        {
            printf("������������ԣ�");
            new_data();
        }
    flag=1;
    printf("�����복����ţ�");
    SaleRecord a;
    Car b;
    scanf("%s",a.carID);
    printf("������������ͣ�1-���룬2-Ԥ����3-�˶���4-��������");
    scanf("%d",&a.action);
    printf("������������ڣ���ʽ��YYYYMMDD����");
    scanf("%s",a.date);
    printf("������������ã�");
    scanf("%f", &a.cost);
    printf("�������ԱID��");
    scanf("%s", a.memberID);
    printf("������Ա�����ţ�");
    scanf("%s", a.employeeID);

    if(a.action==1)
    {
        printf("���ڹ�����һ���³��������������복����Ϣ");
        strcpy(b.carID,a.carID);
        printf("������Ʒ�ƣ�");
        scanf("%s", b.brand);
        printf("�������ͺţ�");
        scanf("%s", b.model);
        printf("���������ͣ����磺1-�ͳ���2-�糵����");
        scanf("%d", &b.type);
        printf("�����복�䣺");
        scanf("%d", &b.age);
        printf("��������̣���λ�������");
        scanf("%f", &b.mileage);
        printf("�����복����1-10����");
        scanf("%d", &b.condition);
        printf("�������Ƿ������¹ʣ�0-�ޣ�1-�У���");
        scanf("%d", &b.accident);
        printf("�������������ã�");
        scanf("%f", &b.prepCost);
        printf("�������³����ۣ�");
        scanf("%f", &b.newCarPrice);
        printf("������Ԥ���ۼۣ�");
        scanf("%f", &b.estimatedPrice);
        carData[carCount]=b;
        saleData[saleCount]=a;
        carCount++;
        saleCount++;
    }
    else if(a.action==4)
    {
        int i,flag=0;
        for(i=0;i<carCount;i++)
        {
            if(strcmp(a.carID,carData[i].carID)==0)
                flag=i;
        }
        for(i=flag;i<carCount-1;i++)
        {
            carData[i]=carData[i+1];
        }
        carCount--;
        saleData[saleCount]=a;
        saleCount++;
    }
    else
    {
        saleData[saleCount]=a;
        saleCount++;
    }
    data_keep();
    printf("�Ƿ��������������y/f)");
    char q;
    scanf("%c",&q);
    if(q=='y'||q=='Y')
        new_data();
    else
        press();
}

//������ĵ���Ϣ
void data_keep()
{

//���泵����Ϣ���ļ�
    FILE *carFile = fopen("cardata.txt", "w");
    if (carFile == NULL)
    {
        printf("�޷��򿪳��������ļ����б��棡\n");
        return;
    }
    for (int i = 0; i < carCount; i++)
    {
        fprintf(carFile, "%s %s %s %d %.2f %d %d %.2f %.2f %.2f\n",
                carData[i].carID, carData[i].brand, carData[i].model,
                carData[i].type, carData[i].mileage, carData[i].condition,
                carData[i].accident, carData[i].prepCost, carData[i].newCarPrice,
                carData[i].estimatedPrice);
    }
    fclose(carFile);

    // ����������Ϣ���ļ�
    FILE *saleFile = fopen("saledata.txt", "w");
    if (saleFile == NULL)
    {
        printf("�޷���������Ϣ�ļ����б��棡\n");
        return;
    }

    for (int i = 0; i < saleCount; i++)
    {
        fprintf(saleFile, "%s %d %s %.2f %s %s\n", saleData[i].carID, saleData[i].action,
                saleData[i].date, saleData[i].cost, saleData[i].memberID, saleData[i].employeeID);
    }
    fclose(saleFile);
    printf("���ݱ���ɹ���\n");
    if(f==0);
}

// ������
int main()
{
    int choice;
    // ��������
    loadCarData();
    loadSaleData();
    mainscreen();
    return 0;
}

