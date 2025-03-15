#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_RECORDS 50
#define MAX_STRING 20
// 车辆数据结构
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

// 操作记录数据结构
typedef struct sale
{
    char carID[MAX_STRING];
    int action;
    char date[MAX_STRING];
    float cost;
    char memberID[MAX_STRING];
    char employeeID[MAX_STRING];
} SaleRecord;

// 全局数据数组
int f=0;
Car carData[MAX_RECORDS];//临时储存数据，拿下来方便一点
SaleRecord saleData[MAX_RECORDS];
int carCount = 0//车辆共有多少台
               , saleCount = 0;//sale有多少条信息


// 函数声明
//懒得声明函数，所以我把主函数放最后面了0.0
// 加载车辆数据
void loadCarData()
{
    FILE *file = fopen("cardata.txt", "r");//只读
    if (file==NULL)
    {
        printf("无法打开文件 cardata.txt\n");//鲁棒性
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
                  &carData[carCount].estimatedPrice) == 11)//同时输入并判断有没有到底
    {
        carCount++;//记录条数
    }

    fclose(file);
}

// 加载操作记录数据，同上
void loadSaleData()
{
    FILE *file = fopen("./saledata.txt", "r");
    if (!file)
    {
        printf("无法打开文件saledata.txt\n");
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
//过渡功能
void press()
{
    char a;
    printf("按回车键以返回主菜单...");
    while (getchar() != '\n');  // 清空缓冲区中的其他字符
    scanf("%c", &a);            // 等待换行符
    mainscreen();
}
#define ADMIN_PASSWORD "admin123"
// 管理员密码
int check_admin_password()
{
    char password[MAX_STRING];
    printf("请输入管理员密码: ");
    scanf("%s", password);
    return strcmp(password, ADMIN_PASSWORD) == 0;//输出是不是的结果，用于判断
}
//主页面
int mainscreen()
{
    int choice,flag=0;//flag判断是否要再进主页面
    while (1)
    {
        printf("       ______               ______\n"        );
        printf("      /|_||_\\`.__         /|_||_\\`.__\n"   );
        printf("     (   _    _ _\\       (   _    _ _\\\n"  );
        printf("     =`-(_)--(_)-'        =`-(_)--(_)-'\n"   );
        printf("======== 二手车交易系统 ========\n");
        printf("1. 查询\n");
        printf("2. 排序\n");
        printf("3. 输出数据\n");
        printf("4. 修改数据\n");
        printf("5. 新增数据\n");
        printf("6. 统计数据\n");
        printf("7. 保存数据并退出\n");
        printf("0. 退出系统\n");
        printf("==========================\n");
        printf("请选择功能（输入数字）：");
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
            printf("是否保存更改？（1-是/2-否）");//提示保存更改
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
                printf("退出系统中...\n");
                return 0;
            }
        default:
            printf("无效输入，请重新选择！\n");
            flag=1;
            break;
        }
        if(flag==1)
            continue;
        else
            break;
    }

}
//查找功能菜单
void search()
{
    int a;
    printf("======== 查询功能 ========\n");
    printf("1. 按里程和车况\n");
    printf("2. 指定员工的操作记录\n");
    printf("3. 按新车价和预估价\n");
    printf("4. 按是否发生事故\n");
    printf("5. 按会员号查询\n");
    printf("0. 退出至主页面\n");
    printf("==========================\n");
    printf("请选择功能（输入数字）：");
    scanf("%d", &a);
    switch(a)
    {
    case 1:
        queryCarsByMileageAndCondition();//功能1
        break;
    case 2:
        queryEmployeeRecords();//功能2
        break;
    case 3:
        queryNewPre();//功能3
        break;
    case 4:
        queryAnci();//功能4
        break;
    case 5:
        vip();
        break;
    default:
        printf("输入错误！请重试：");
        search();
        break;
    case 0://退出
        mainscreen();
        break;
    }
    press();
}
// 查询指定里程以内和车况的车辆
void queryCarsByMileageAndCondition()
{
    float maxMileage;
    int minCondition;
    //两个查找条件
    printf("请输入最大里程（单位：万公里，示例：10.0）：");
    scanf("%f", &maxMileage);
    printf("请输入最低车况（1到10，示例：8）：");
    scanf("%d", &minCondition);

    printf("符合条件的车辆如下：\n");
    printf("车辆编号\t品牌\t\t型号\t里程\t车况\t预估售价\n");
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

// 查询指定员工的所有操作记录
void queryEmployeeRecords()
{
    char employeeID[MAX_STRING];
    printf("请输入员工工号（示例：E001）：");
    scanf("%s", employeeID);//查找条件
    printf("该员工的操作记录如下：\n");
    printf("车辆编号\t操作类型\t日期\t\t操作费用\n");
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
    printf("请输入会员号（示例：M001）：");
    scanf("%s", vipID);//查找条件
    printf("该会员的操作记录如下：\n");
    printf("车辆编号\t操作类型\t日期\t\t操作费用\n");
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
//查询新车价和预估价
void queryNewPre()
{
    float maxNew;
    int minPre;
//查找条件
    printf("请输入最高新车价位：(数字）");
    scanf("%f", &maxNew);
    printf("请输入最低预测价位：（数字）");
    scanf("%d", &minPre);

    printf("符合条件的车辆如下：\n");
    printf("车辆编号\t品牌\t\t型号\t里程\t车况\t预估售价\n");
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
//按是否发生事故查询
void queryAnci()
{

    int a;
    printf("请输入你的需求：（1-是/0-否）");
    scanf("%f", &a);
    printf("符合条件的车辆如下：\n");
    printf("车辆编号\t品牌\t\t型号\t里程\t车况\t预估售价\n");
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
//排序功能菜单
void sort()
{
    int a;
    printf("======== 排序功能 ========\n");
    printf("1. 在售车按品牌进行排序\n");
    printf("2. 在售车按预估售卖价进行排序\n");
    printf("3. 按里程数进行排序\n");
    printf("4. 按维修价进行排序\n");
    printf("0. 退出至主菜单\n");
    printf("==========================\n");
    printf("请选择功能（输入数字）：");
    scanf("%d", &a);
    switch(a)
    {
    case 1:
        printf("\n\n");
        sort_brand();//功能1
        break;
    case 2:
        printf("\n\n");
        sort_predict();//功能2
        break;
    case 3:
        printf("\n\n");
        sort_mileage();//功能3
        break;
    case 4:
        printf("\n\n");//功能4
        sort_p();
        break;
    default:
        printf("输入错误！请重试：");
        sort();
        break;
    case 0:
        mainscreen();
        break;
    }
    press();
}
// 按品牌排序（冒泡排序）
void sort_brand()
{
    for (int i=0; i<carCount-1; i++)
    {
        for (int j=0; j<carCount-1-i; j++)
        {
            if (strcmp(carData[j].brand, carData[j + 1].brand)>0)
            {
                // 交换两条记录
                Car temp;
                temp=carData[j];
                carData[j]=carData[j + 1];
                carData[j + 1]=temp;
            }
        }
    }
    printf("车辆编号\t品牌\t\t型号\t\t类型\t车龄\t里程\t车况\t事故\t整备费用\t新车报价\t预估售价\n");
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
//按预测价格排序
void sort_predict()
{
    for (int i=0; i<carCount-1; i++)
    {
        for (int j=0; j<carCount-1-i; j++)
        {
            if (carData[j].estimatedPrice>carData[j+1].estimatedPrice)
            {
                // 交换两条记录
                Car temp;
                temp=carData[j];
                carData[j] = carData[j+1];
                carData[j+1]=temp;
            }
        }
    }
    printf("车辆编号\t品牌\t\t型号\t\t类型\t车龄\t里程\t车况\t事故\t整备费用\t新车报价\t预估售价\n");
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
//按里程数排序
void sort_mileage()
{
    for (int i=0; i<carCount-1; i++)
    {
        for (int j=0; j<carCount-1-i; j++)
        {
            if (carData[j].mileage>carData[j+1].mileage)
            {
                // 交换两条记录
                Car temp;
                temp= carData[j];
                carData[j] = carData[j+1];
                carData[j+1] = temp;
            }
        }
    }
    printf("车辆编号\t品牌\t型号\t\t\t类型\t车龄\t里程\t车况\t事故\t整备费用\t新车报价\t预估售价\n");
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
//按维修费排序
void sort_p()
{
    for (int i=0; i<carCount-1; i++)
    {
        for (int j=0; j<carCount-1-i; j++)
        {
            if (carData[j].prepCost>carData[j+1].prepCost)
            {
                // 交换两条记录
                Car temp;
                temp=carData[j];
                carData[j]=carData[j+1];
                carData[j+1]=temp;
            }
        }
    }
    printf("车辆编号\t品牌\t型号\t\t\t类型\t车龄\t里程\t车况\t事故\t整备费用\t新车报价\t预估售价\n");
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
//输出主页面
void output()
{
    int a;
    printf("======== 输出 ========\n");
    printf("1. 输出车辆信息\n");
    printf("2. 输出销售记录\n");
    printf("3. 退出至主页面\n");
    printf("==========================\n");
    printf("请选择功能（输入数字）：");
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
        printf("输入错误！请重试：");
        output();
        break;
    }
    press();
}
//输出cardata.txt**有问题
void output_car()
{
    int count=0,flag=1,i=0;
    for(i=0; i<carCount; i++)
    {
        if(count==0)
        {
            printf("编号\t品牌\t\t型号\t\t类型\t车龄\t车况\t事故\t里程\t整备费用\t新车价格\t预估售价\n");
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
                printf("**当前为第%d页，共%d页，按1以上一页，按2下一页...**",flag,carCount/10+1);
                int a;
                scanf("%d", &a); // 等待指令
                if(a==1)
                {
                    if(i==10)//当为第一页时，无法上一页
                        i-=10;
                    else//不为第一页时
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
//输出销售记录
void output_sale()
{
    int count=0,flag=1,i=0;
    for(i=0; i<saleCount; i++)
    {
        if(count==0)
        {
            printf("编号\t操作\t日期\t操作费用\t用户会员号\t员工工号\n");
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
            printf("**当前为第%d页，共%d页，按1以上一页，按2下一页...**",flag,saleCount/10+1);
            int a;
            scanf("%d", &a); // 等待指令
            if(a==1)
            {
                if(i==10)//当为第一页时，无法上一页
                    i-=10;
                else//不为第一页时
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

//修改记录，需密码
void revise()
{
    int a;
    if(check_admin_password()==0)
    {
        printf("密码错误，无法执行修改操作！");
        fflush(stdin);
        mainscreen();
    }
    printf("登录成功！\n");
    printf("======== 修改 ========\n");
    printf("1. 修改销售记录中的对接工人\n");
    printf("2. 修改预定费用\n");
    printf("3. 修改车辆相关信息\n");
    printf("0. 退出至主页面\n");
    printf("==========================\n");
    printf("请选择功能（输入数字）：");
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
        printf("暂无对应选项！请重试：");
        revise();
        break;
    }

}
//修改对接工人
void revise_emp()
{
    int flag=0;
    char a[20];
    char b[20];
    int i;
    printf("请输入车辆编号（示例：C001）：");
    scanf("%s",a);
    for (i=0,flag=0; i<saleCount; i++)
    {
        if (strcmp(saleData[i].carID,a)==0)
        {
            printf("修改为：");
            scanf("%s",b);
            strcpy(saleData[i].employeeID,b);
            flag=1;
            break;
        }

    }
    if(flag==1)
        printf("修改成功！\n");
    else if(flag==0)
    {
        printf("输入错误，");
        revise_emp();
    }
    data_keep();
    press();
}
//修改预约价格
void revise_precost()
{
    int flag=0;
    char a[20];
    float b;
    int i;
    printf("请输入车辆编号（示例：C001）：");
    scanf("%s",&a);
    fflush(stdin);
    for (i=0,flag=0; i<saleCount; i++)
    {
        if (saleData[i].action==2&&strcmp(saleData[i].carID,a)==0)
        {
            printf("修改为：");
            scanf("%f",&b);
            saleData[i].cost=b;
            flag=1;
            break;

        }
    }
    if(flag==1)
    printf("修改成功！");
    else if(flag==0&&saleData[i].action!=2)
    {
        printf("这辆车没有被预约！");
    }
    else if(flag==0)
    {
       printf("输入错误，");
     revise_emp();
    }
    data_keep();
    press();
}
//修改车辆信息（编号和型号不可修改）
void revise_car()
{
    char car_id[MAX_STRING];
    printf("请输入要修改的车辆的编号：（示例C001)");
    scanf("%s",car_id);
    int flag=0,i;
    for(i=0; i<carCount; i++)
    {
        if(strcmp(car_id,carData[i].carID)==0)
        {
            printf("请输入品牌：（品牌名）");
            scanf("%s", carData[i].brand);
            printf("请输入型号：（型号）");
            scanf("%d", &carData[i].model);
            printf("请输入车龄：(数字）");
            scanf("%d", &carData[i].age);
            printf("请输入里程（单位：万公里）：");
            scanf("%f", &carData[i].mileage);
            printf("请输入车况（1-10）：");
            scanf("%d", &carData[i].condition);
            printf("请输入是否发生过事故（0-无，1-有）：");
            scanf("%d", &carData[i].accident);
            printf("请输入整备费用：");
            scanf("%f", &carData[i].prepCost);
            printf("请输入新车报价：");
            scanf("%f", &carData[i].newCarPrice);
            printf("请输入预估售价：");
            scanf("%f", &carData[i].estimatedPrice);
            flag=1;
        }
    }
    if(flag==0)
    {
        printf("该编号不存在！请重试。");
        revise_car();
    }
    else
    {
        printf("修改成功！");
        press();
        data_keep();
    }
}

//统计主页面
void counting()
{
    int a;
    printf("======== 统计 ========\n");
    printf("1. 公司盈亏状态\n");
    printf("2. 当前销售冠军\n");
    printf("3. 最受欢迎的车辆品牌\n");
    printf("4. 最不受欢迎的车辆品牌\n");
    printf("0. 退出至主页面\n");
    printf("==========================\n");
    printf("请选择功能（输入数字）：");
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
        printf("输入错误！请重试");
        counting();
        break;
    }
}
//统计公司盈亏
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
    printf("当前公司总盈亏为：%.1f万元\n",sum);
    press();
}
//统计谁是销冠(参与记录最多）**有问题
void sale_champion()
{
    int maxCount = 0;
    char champion[MAX_STRING];

    // 统计每个员工参与操作记录的次数
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

    // 输出销冠
    printf("销售冠军为：员工工号 %s，参与次数：%d\n", champion, maxCount);
    press();
}

//最受欢迎的汽车品牌
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

    printf("最受欢迎的品牌：\n");
    for (int i = 0; i < brandIndex; i++)
    {
        if (brandCount[i] == maxCount)
        {
            printf("%s\n", brands[i]);
        }
    }
    press();
}
//最不受欢迎的品牌
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

    printf("最不受欢迎的品牌：\n");
    for (int i = 0; i < brandIndex; i++)
    {
        if (brandCount[i] == minCount)
        {
            printf("%s\n", brands[i]);
        }
    }
    press();
}
//新增数据
void new_data()
{
    int flag=0;
    int choice;
    if(flag==0)
        if(check_admin_password()==0)
        {
            printf("密码错误，请重试！");
            new_data();
        }
    flag=1;
    printf("请输入车辆编号：");
    SaleRecord a;
    Car b;
    scanf("%s",a.carID);
    printf("请输入操作类型（1-买入，2-预定，3-退订，4-卖出）：");
    scanf("%d",&a.action);
    printf("请输入操作日期（格式：YYYYMMDD）：");
    scanf("%s",a.date);
    printf("请输入操作费用：");
    scanf("%f", &a.cost);
    printf("请输入会员ID：");
    scanf("%s", a.memberID);
    printf("请输入员工工号：");
    scanf("%s", a.employeeID);

    if(a.action==1)
    {
        printf("由于购入了一辆新车，接下来需输入车辆信息");
        strcpy(b.carID,a.carID);
        printf("请输入品牌：");
        scanf("%s", b.brand);
        printf("请输入型号：");
        scanf("%s", b.model);
        printf("请输入类型（例如：1-油车，2-电车）：");
        scanf("%d", &b.type);
        printf("请输入车龄：");
        scanf("%d", &b.age);
        printf("请输入里程（单位：万公里）：");
        scanf("%f", &b.mileage);
        printf("请输入车况（1-10）：");
        scanf("%d", &b.condition);
        printf("请输入是否发生过事故（0-无，1-有）：");
        scanf("%d", &b.accident);
        printf("请输入整备费用：");
        scanf("%f", &b.prepCost);
        printf("请输入新车报价：");
        scanf("%f", &b.newCarPrice);
        printf("请输入预估售价：");
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
    printf("是否还需继续新增？（y/f)");
    char q;
    scanf("%c",&q);
    if(q=='y'||q=='Y')
        new_data();
    else
        press();
}

//保存更改的信息
void data_keep()
{

//保存车辆信息到文件
    FILE *carFile = fopen("cardata.txt", "w");
    if (carFile == NULL)
    {
        printf("无法打开车辆数据文件进行保存！\n");
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

    // 保存销售信息到文件
    FILE *saleFile = fopen("saledata.txt", "w");
    if (saleFile == NULL)
    {
        printf("无法打开销售信息文件进行保存！\n");
        return;
    }

    for (int i = 0; i < saleCount; i++)
    {
        fprintf(saleFile, "%s %d %s %.2f %s %s\n", saleData[i].carID, saleData[i].action,
                saleData[i].date, saleData[i].cost, saleData[i].memberID, saleData[i].employeeID);
    }
    fclose(saleFile);
    printf("数据保存成功！\n");
    if(f==0);
}

// 主函数
int main()
{
    int choice;
    // 加载数据
    loadCarData();
    loadSaleData();
    mainscreen();
    return 0;
}

