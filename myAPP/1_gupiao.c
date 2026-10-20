#include <stdio.h>
#include <windows.h>


int main() {
    SetConsoleOutputCP(CP_UTF8);

    double cost, market, num;
    double balance, profit, gain;

    printf("请输入买入单价: ");
    scanf("%lf", &cost);

    printf("请输入当前单价: ");
    scanf("%lf", &market);

    printf("请输入持股数量: ");
    scanf("%lf", &num);

    balance = 12000;                       /* 初始余额（暂定固定值） */
    balance = balance - cost * num;        /* 买入扣钱 */

    gain = (market - cost) / cost * 100;   /* 涨跌幅 % */
    profit = market - cost;                /* 每股盈亏 */

    printf("------------------------\n");

    if (gain >= 0) {
        printf("涨: %.2f%%\n", gain);
        printf("赚: %.2f 倍\n", gain / 100);
        //printf("盈: %.2f 元/股\n", profit);
    } else {
        printf("跌: %.2f%%\n", gain);
        printf("亏: %.2f 倍\n", gain / 100);
        //printf("盈: %.2f 元/股\n", profit);
    }
	printf("盈: %.2f 元/股\n", profit);
    printf("------------------------\n");
	printf("成本: %.2f 元\n", cost * num);
    printf("盈利: %.2f 元\n", (market - cost) * num);
    printf("余额: %.2f 元\n", (cost * num) + (profit*num));
	
    return 0;
}

