#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <sys/time.h>
#define KETA 1005             //桁数
#define INTEGER (5)               //整数桁
#define DECIMAL (KETA - INTEGER)   //少数桁

struct NUMBER{
    int n[KETA];//数
    int sign;   //符号 
    int exp;    //指数
};

int setSign(struct NUMBER *a, int s);//sが1なら正, sが-1なら負にする
int getSign(struct NUMBER *a);//aが正なら1, aが負なら-1を返す
void setExp(struct NUMBER *a, int e);//expにeを設定する
void clearByZero(struct NUMBER *a);//初期化
void copyNumber(struct NUMBER *a, struct NUMBER *b);//aをbにコピーする(copyNumber内初期化:b)
void dispNumber(struct NUMBER *a);//符号,数値,指数を表示
int mulBy10(struct NUMBER *a, struct NUMBER *b);//aを10倍にしてbに返す(mulBy10内初期化:b)
int divBy10(struct NUMBER *a, struct NUMBER *b);//aを1/10にしてbに返す(divBy10内初期化:b)
int setNum(struct NUMBER *a, int x, int e);//数字を設定 (a:多倍長(1.234),x:数字(1234)e:10の指数(10^-3))(setNum内初期化:a)
int isZero(struct NUMBER *a);//aがゼロか判別する(0:value=0, !0:value=-1)
void getAbs(struct NUMBER *a, struct NUMBER *b);//aの絶対値をbに返す(getAbs内初期化:b)
int numComp(struct NUMBER *a, struct NUMBER *b);//2つの多倍長を比べる,戻り値(0:a==b)(1:a>b)(-1:a<b)
int add(struct NUMBER *a, struct NUMBER *b, struct NUMBER *c);//足し算(a+b=c)(add内初期化:c)
int sub(struct NUMBER *a, struct NUMBER *b, struct NUMBER *c);//引き算(a-b=c)(sub内初期化:c)
int multiple(struct NUMBER *a, struct NUMBER *b, struct NUMBER *c);//かけ算(a*b=c)(multiple内初期化:c)
int divide(struct NUMBER *a, struct NUMBER *b, struct NUMBER *c);//割り算(a/b=c)(divide内初期化:c)
void Dase(struct NUMBER *pi);//ダーゼの公式(dase内初期化:pi)
void Vega(struct NUMBER *pi);//ベガの公式(Vega内初期化:pi)
void Stellmers(struct NUMBER *pi);//シュテルマーの公式(Stellmers内初期化:pi)
void arctan(int a, struct NUMBER *arc);//アークタンジェントを求める(arctan内初期化:arc)

int setSign(struct NUMBER *a, int s){
    if(s == 1){//正のとき
        a->sign = 1;
    }
    else if(s == -1){//負のとき
        a->sign = 0;
    }
    else{//エラー
        return -1;
    }
    return 0;
}

int getSign(struct NUMBER *a){
    if(a->sign == 1){//正のとき
        return 1;
    }
    else if(a->sign == 0){//負のとき
        return -1;
    }
    return 0;
}

void setExp(struct NUMBER *a, int e){
    a->exp = e;//eの値を格納
}

void clearByZero(struct NUMBER *a){
    int i;
    for(i = 0;i < KETA;i++){//配列の中身を全て0にする
        a->n[i] = 0;
    }
    setExp(a, 0); //0.e0にする
    setSign(a, 1); //符号をプラス側にセット
}

void copyNumber(struct NUMBER *a, struct NUMBER *b){
    clearByZero(b);//初期化
    *b = *a;//コピー
}

void dispNumber(struct NUMBER *a){
    int i;

    if(getSign(a)==1){//符号+
        printf("+");
    }
    else if(getSign(a)==-1){//符号-
        printf("-");
    }
    else{//エラー
        printf("error");
    }

    for(int i = 1; i <= KETA; i++){//多倍長
        printf("%d",a->n[KETA - i]);
        if(INTEGER == i){
            printf(".");
        }
    }
    printf("\ne%d", a->exp);//指数
}

int mulBy10(struct NUMBER *a, struct NUMBER *b){
    int i = 0;
    clearByZero(b);//初期化
    b->sign = a->sign;//符号
    b->exp = a->exp;//指数
    if(a->n[KETA - 1] == 0){//10倍
        for(i = 0;i < KETA - 1;i++){
            b->n[i + 1] = a->n[i];
        }
        b->n[0] = 0;
    }
    else{
        return -1;
    }
    return 0;
}

int divBy10(struct NUMBER *a, struct NUMBER *b){
    int value = 0, i;
    clearByZero(b);
    b->sign = a->sign;//符号
    b->exp = a->exp;//指数
    b->n[KETA - 1] = 0;
    for(i = 0;i < KETA - 1;i++){//0.1倍
        b->n[i] = a->n[i + 1];
    }

    if(getSign(a)==1){//余りが正
        value = a->n[0];
    }
    else{//余りが負
        value = a->n[0] * -1;
    }
    return value;
}

int setNum(struct NUMBER *a, int x, int e){
    struct NUMBER tmp;
    int dif = 0, i = DECIMAL, n = 10;
    clearByZero(a);
    clearByZero(&tmp);
    
    if(x == 0) return 0;//0のとき
    if(x > 999999999 || x < -999999999) return -1;//エラー

    if(x > 0){//符号が+
        setSign(a, 1);
    }
    else if (x < 0){//符号が-
        setSign(a, -1);
        x = -x;
    }

    while(n < x) n = n * 10;//xの最高位を調べる

    while(n > 1){
        n = n / 10;//10で割る
        dif = x / n;
        x = x - (dif * n);//最高位の値*nを引く
        a->n[i] = dif;//最高位の値を求める
        i--;
    }

    setExp(a, e);//指数

    if(x != 0) return -1;

    return 0;
}

int isZero(struct NUMBER *a){
    int i;

    for(i = 0;i < KETA;i++){//ゼロか判別する
        if(a->n[i] != 0){
            return -1;
        }
    }

    return 0;
}

void getAbs(struct NUMBER *a, struct NUMBER *b){
    clearByZero(b);//初期化
    copyNumber(a, b);//コピー
    setSign(b, 1);//符号+
}

int numComp(struct NUMBER *a, struct NUMBER *b){
    int i;

    if(getSign(a) > getSign(b)){//符号
        return 1;
    }
    else if(getSign(a) < getSign(b)){//符号
        return -1;
    }
    else{
        if(a->exp > b->exp){//指数
            return 1;
        }
        else if(a->exp < b->exp){//指数
            return -1;
        }
        else if(getSign(a) == 1 || getSign(b) == 1){//符号+
            for(i = KETA - 1;i >= 0;i--){
                if(a->n[i] > b->n[i]){
                    return 1;
                }
                if(a->n[i] < b->n[i]){
                    return -1;
                }
            }
        }
        else if(getSign(a) == -1 || getSign(b) == -1){//符号-
            for(i = KETA - 1;i >= 0;i--){
                if(a->n[i] > b->n[i]){
                    return -1;
                }
                if(a->n[i] < b->n[i]){
                    return 1;
                }
            }
        }
    }

    return 0;//同じ
}

int add(struct NUMBER *a, struct NUMBER *b, struct NUMBER *c){
    int i = 0, j = 0, z = 0, e = 0, zExp = 0, wExp = 0;
    struct NUMBER d, f;
    clearByZero(c);
    getAbs(a, &d);
    getAbs(b, &f);

    if(getSign(a) == 1 && getSign(b) == -1){//a:+,b:-
        sub(a, &d, c);
    }
    else if(getSign(a) == -1 && getSign(b) == 1){//a:-,b:+
        sub(b, &d, c);
    }
    else if(getSign(a) == -1 && getSign(b) == -1){//a:-,b:-
        add(&f, &d, c);
        setSign(c, -1);
    }
    else{//a:+,b:+
        if(a->exp >= b->exp){//指数を比べる
            wExp = a->exp;//cの指数
            j = a->exp - b->exp;//指数の差
            zExp = DECIMAL - j;//bの最高位
        }
        else{
            wExp = b->exp;//cの指数
            j = b->exp - a->exp;//指数の差
            zExp = DECIMAL - j;//aの最高位
            getAbs(b, &d);
            getAbs(a, &f);
        }

        for(i = 0;i <= DECIMAL + 1;i++){
            if(i <= zExp){//fの最高桁以下
                z = d.n[i] + f.n[j] + e;//和
                c->n[i] = z % 10;//和の1の位
                e = (z - c->n[i]) / 10;//繰り上がり
                j++;
            }
            else{//fの最高桁以上
                c->n[i] = d.n[i] + e;
                e =0;
            }
        }

        if(c->n[DECIMAL + 1] != 0){//有効桁表示
            divBy10(c, &d);
            copyNumber(&d, c);
            wExp++;
        }
        setExp(c, wExp);//指数
    }

    if(e != 0){
        return -1;
    }

    return 0;
}

int sub(struct NUMBER *a, struct NUMBER *b, struct NUMBER *c){
    int i = 0, j = 0, e = 0, wExp = 0;
    struct NUMBER d, f, tmp;
    clearByZero(&tmp);
    getAbs(a, &d);
    getAbs(b, &f);

    if(getSign(a) == 1 && getSign(b) == -1){//a:+,b:-
        add(a, &f, c);
    }
    else if(getSign(a) == -1 && getSign(b) == 1){//a:-,b:+
        add(&d, b, c);
        setSign(c, -1);
    }
    else if(getSign(a) == -1 && getSign(b) == -1){//a:-,b:-
        sub(&f, &d, c);
    }
    else{//a:+,b:+
        if(numComp(a, b) == -1){//a<b
            sub(b, a, c);
            setSign(c, -1);
        }
        else{
            if(a->exp >= b->exp){//指数を比べる
                wExp = a->exp;//cの指数
                j = a->exp - b->exp;//指数の差
            }
            else{
                wExp = b->exp;//cの指数
                j = b->exp - a->exp;//指数の差
                getAbs(b, &d);
                getAbs(a, &f);
            }

            for(i = 0;i < j;i++){//指数をそろえる
                divBy10(&f, &tmp);
                copyNumber(&tmp, &f);
            }

            for(i = 0;i < KETA;i++){//引き算
                c->n[i] = d.n[i] - f.n[i] - e;//差
                e = 0;
                if(c->n[i] < 0){//マイナスのとき
                    c->n[i] += 10;
                    e = 1;//繰り下がり
                }
            }

            if(isZero(c) != 0){
                while(c->n[DECIMAL] == 0){//有効桁表示
                    mulBy10(c, &d);
                    copyNumber(&d, c);
                    wExp--;
                }
            }
            setExp(c, wExp);//指数
        }
    }
    return 0;
}

int multiple(struct NUMBER *a, struct NUMBER *b, struct NUMBER *c){
    int up = 0, re = 0, exp = a->exp + b->exp, n = 0, i = 0, j = 0;
    struct NUMBER d, e, f, tmp;
    clearByZero(c);
    getAbs(a, &d);
    getAbs(b, &e);
    
    if(isZero(a) == 0 || isZero(b) == 0){//0のとき
        return 0;
    }

    for (i = 0; i < KETA; i++){//かけ算
        clearByZero(&f);
        up = 0;
        re = 0;   
        n = 0;
        if(e.n[i] != 0){//0のとき
            for(j = 0; j < KETA; j++){
                n = i + j - DECIMAL;//桁
                re = d.n[j] * e.n[i] + up;//積
                if(n >= 0){//格納, else切り捨て
                    f.n[n] = re % 10;
                }
                up = (re / 10) % 10;//繰り上がり
            }
            while(f.n[DECIMAL + 1] != 0){//有効桁表示
                divBy10(&f, &tmp);
                copyNumber(&tmp, &f);
                f.exp++;
            }
            add(c, &f, &tmp);//足す
            copyNumber(&tmp, c);
        }
    }

    while(c->n[DECIMAL + 1] != 0){//有効桁表示
        divBy10(c, &tmp);
        copyNumber(&tmp, c);
        exp++;
    }

    setSign(c, getSign(a) * getSign(b));//符号
    setExp(c, exp + c->exp);//指数

    if(up != 0){
        return -1;
    }

    return 0;
}

int divide(struct NUMBER *a, struct NUMBER *b, struct NUMBER *c){
    int i = 0, exp = a->exp - b->exp;
    struct NUMBER d, e, f, g, h, one, ten;
    clearByZero(c);//商
    clearByZero(&d);//bを大きくする
    clearByZero(&e);//引いた数だけ格納
    clearByZero(&h);//コピーとかで使う
    clearByZero(&one);//1を格納
    getAbs(a, &f);
    getAbs(b, &g);
    setNum(&one, 1, 0);

    if(isZero(a) == 0){//0のとき
        return -1;
    }
    if(isZero(b) == 0){//0のとき
        return -1;
    }
    if(numComp(a, b) == 0){
        setNum(c, 1, 0);
        setSign(c, getSign(a) * getSign(b));
        return 0;
    }

    if(numComp(&f, &g) == -1 || f.exp == g.exp){//gの方が大きい,指数が同じ
        exp--;
    }

    g.exp = a->exp - DECIMAL;
    
    while(numComp(&f, &g) != -1){//(f<g)
        if(isZero(&f) == 0){//(f=0)
            break;
        }
        copyNumber(&g, &d);
        copyNumber(&one, &e);
        while(numComp(&f, &d) != -1){//gがfより小さい最大の値
            d.exp++;
            e.exp++;
        }
        d.exp--;
        e.exp--;
        sub(&f, &d, &h);//fから引く
        copyNumber(&h, &f);
        add(c, &e, &h);//商を求める
        copyNumber(&h, c);
        while(c->n[DECIMAL] == 0){
            mulBy10(c, &d);
            copyNumber(&d, c);
            exp--;
        }
    }
    
    setExp(c, exp);
    setSign(c, getSign(a) * getSign(b));
    return 0;
}

void Dase(struct NUMBER *pi){
    int denominator = 1;//分母を格納(初期:1)
    int carry = 0;//逆数のときに使う
    int i = 0;//for文で使う
    struct NUMBER one, two, four, five, eight;//数字
    struct NUMBER one2, one5, one8;//逆数
    struct NUMBER power2, power5, power8;//2乗
    struct NUMBER item2, item5, item8;//係数
    struct NUMBER arctan2, arctan5, arctan8;//arctan
    struct NUMBER empty, number, coefficient;//その他
    
    clearByZero(&empty);//コピーのときとかに使う

    setNum(&one, 1, 0);//1.e0を格納
    setNum(&two, 2, 0);//2.e0を格納
    setNum(&four, 4, 0);//4.e0を格納
    setNum(&five, 5, 0);//5.e0を格納
    setNum(&eight, 8, 0);//8.e0を格納

    divide(&one, &two, &one2);//(1/2)^(2i+1)を格納
    copyNumber(&one2, &empty);
    multiple(&one2, &empty, &power2);//(1/2)^2を格納
    clearByZero(&item2);//{1/(2i+1)}*(1/2)^(2i+1)を格納
    clearByZero(&arctan2);//arctan(1/2)を格納

    divide(&one, &five, &one5);//(1/5)^(2i+1)を格納
    copyNumber(&one5, &empty);
    multiple(&one5, &empty, &power5);//(1/5)^2を格納
    clearByZero(&item5);//{1/(2i+1)}*(1/5)^(2i+1)を格納
    clearByZero(&arctan5);//arctan(1/5)を格納

    divide(&one, &eight, &one8);//(1/8)^(2i+1)を格納
    copyNumber(&one8, &empty);
    multiple(&one8, &empty, &power8);//(1/8)^2を格納
    clearByZero(&item8);//{1/(2i+1)}*(1/8)^(2i+1)を格納
    clearByZero(&arctan8);//arctan(1/8)を格納

    clearByZero(&number);//1/aを格納
    clearByZero(&coefficient);//iのときの係数{1/(2i+1)}を格納
    clearByZero(pi);//計算したpiを格納

    while(item2.exp >= -(DECIMAL+1)){
        if(denominator < 10) carry = 0;//有効数字調整
        else if(denominator < 100) carry = 1;
        else if(denominator < 1000) carry = 2;
        else carry = 3;
        setNum(&number, denominator, carry);//分母を格納(i+=1:denominator+=2)
        divide(&one, &number, &coefficient);//1/denominatorを格納

        //arctan(1/2)
        multiple(&coefficient, &one2, &item2);//{1/(2i+1)}*(1/2)^(2i+1)
        if(i % 2 == 0){//iが偶数のとき
            add(&arctan2, &item2, &empty);//arctan(1/2)を求める
            copyNumber(&empty, &arctan2);
        }
        else{//iが奇数のとき
            sub(&arctan2, &item2, &empty);//arctan(1/2)を求める
            copyNumber(&empty, &arctan2);
        }
        multiple(&one2, &power2, &empty);
        copyNumber(&empty, &one2);

        //arctan(1/5)
        if(item5.exp >= -(DECIMAL + 1)){//arctan(1/5)
            multiple(&coefficient, &one5, &item5);//{1/(2i+1)}*(1/5)^(2i+1)
            if(i % 2 == 0){//iが偶数のとき
                add(&arctan5, &item5, &empty);//arctan(1/5)を求める
                copyNumber(&empty, &arctan5);
            }
            else{//iが奇数のとき
                sub(&arctan5, &item5, &empty);//arctan(1/5)を求める
                copyNumber(&empty, &arctan5);
            }
            multiple(&one5, &power5, &empty);
            copyNumber(&empty, &one5);
        }

        //arctan(1/8)
        if(item8.exp >= -(DECIMAL + 1)){//arctan(1/8)
            multiple(&coefficient, &one8, &item8);//{1/(2i+1)}*(1/8)^(2i+1)
            if(i % 2 == 0){//iが偶数のとき
                add(&arctan8, &item8, &empty);//arctan(1/8)を求める
                copyNumber(&empty, &arctan8);
            }
            else{//iが奇数のとき
                sub(&arctan8, &item8, &empty);//arctan(1/8)を求める
                copyNumber(&empty, &arctan8);
            }
            multiple(&one8, &power8, &empty);
            copyNumber(&empty, &one8);
        }

        denominator += 2;//分母を2増やす
        i++;//nを増やす
    }

    add(&arctan2, &arctan5, pi);
    add(pi, &arctan8, &empty);//合計
    multiple(&empty, &four, pi);//4倍
}

void Vega(struct NUMBER *pi){
    int denominator = 1;//分母を格納(初期:1)
    int carry = 0;//逆数のときに使う
    int i = 0;//for文で使う
    struct NUMBER one, two, four, seven, eight;//数字
    struct NUMBER one2, one7;//逆数
    struct NUMBER power2, power7;//2乗
    struct NUMBER item2, item7;//係数
    struct NUMBER arctan2, arctan7;//arctan
    struct NUMBER empty, number, coefficient, a, b;//その他

    clearByZero(&empty);

    setNum(&one, 1, 0);//1を格納
    setNum(&two, 2, 0);//2を格納
    setNum(&four, 4, 0);//4を格納
    setNum(&seven, 7, 0);//7を格納
    setNum(&eight, 8, 0);//8を格納

    divide(&one, &two, &one2);//1/2
    copyNumber(&one2, &empty);
    multiple(&one2, &empty, &power2);//(1/2)^2
    setNum(&item2, 1, 0);
    clearByZero(&arctan2);

    divide(&one, &seven, &one7);//1/7
    copyNumber(&one7, &empty);
    multiple(&one7, &empty, &power7);//(1/7)^2
    setNum(&item7, 1, 0);
    clearByZero(&arctan7);

    clearByZero(&number);
    clearByZero(&coefficient);
    clearByZero(&a);
    clearByZero(&b);
    clearByZero(pi);//計算したpiを格納

    while(item2.exp >= -(DECIMAL+1)){
        if(denominator < 10) carry = 0;//有効数字調整
        else if(denominator < 100) carry = 1;
        else if(denominator < 1000) carry = 2;
        else carry = 3;
        setNum(&number, denominator, carry);//分母を格納(i+=1:denominator+=2)
        divide(&one, &number, &coefficient);//1/denominatorを格納

        //arctan(1/2)
        multiple(&coefficient, &one2, &item2);//{1/(2i+1)}*(1/2)^(2i+1)
        if(i % 2 == 0){//iが偶数のとき
            add(&arctan2, &item2, &empty);//arctan(1/2)を求める
            copyNumber(&empty, &arctan2);
        }
        else{//iが奇数のとき
            sub(&arctan2, &item2, &empty);//arctan(1/2)を求める
            copyNumber(&empty, &arctan2);
        }
        multiple(&one2, &power2, &empty);
        copyNumber(&empty, &one2);

        //arctan(1/7)
        if(item7.exp >= -(DECIMAL + 1)){//arctan(1/7)
            multiple(&coefficient, &one7, &item7);//{1/(2i+1)}*(1/7)^(2i+1)
            if(i % 2 == 0){//iが偶数のとき
                add(&arctan7, &item7, &empty);//arctan(1/5)を求める
                copyNumber(&empty, &arctan7);
            }
            else{//iが奇数のとき
                sub(&arctan7, &item7, &empty);//arctan(1/5)を求める
                copyNumber(&empty, &arctan7);
            }
            multiple(&one7, &power7, &empty);
            copyNumber(&empty, &one7);
        }

        denominator += 2;
        i++;
    }

    multiple(&arctan2, &eight, &a);//8倍
    multiple(&arctan7, &four, &b);//4倍
    sub(&a, &b, pi);//合計
}

void Stellmers(struct NUMBER *pi){
    int denominator = 1;//分母を格納(初期:1)
    int carry = 0;//逆数のときに使う
    int i = 0;//for文で使う
    struct NUMBER one, num1, num2, num3, num4;//数字
    struct NUMBER onesevensix, twoeight, foureight, ninesix;
    struct NUMBER one1, one2, one3, one4;//逆数
    struct NUMBER power1, power2, power3, power4;//2乗
    struct NUMBER item1, item2, item3, item4;//係数
    struct NUMBER arctan1, arctan2, arctan3, arctan4;//arctan
    struct NUMBER tmp1, tmp2, tmp3, tmp4;//置き換え
    struct NUMBER empty, number, coefficient;//その他

    clearByZero(&empty);

    setNum(&one, 1, 0);
    setNum(&num1, 57, 1);
    setNum(&num2, 239, 2);
    setNum(&num3, 682, 2);
    setNum(&num4, 12943, 4);
    setNum(&onesevensix, 176, 2);
    setNum(&twoeight, 28, 1);
    setNum(&foureight, 48, 1);
    setNum(&ninesix, 96, 1);

    divide(&one, &num1, &one1);
    copyNumber(&one1, &empty);
    multiple(&one1, &empty, &power1);
    setNum(&item1, 1, 0);
    clearByZero(&arctan1);
    clearByZero(&tmp1);

    divide(&one, &num2, &one2);
    copyNumber(&one2, &empty);
    multiple(&one2, &empty, &power2);
    setNum(&item2, 1, 0);
    clearByZero(&arctan2);
    clearByZero(&tmp2);

    divide(&one, &num3, &one3);
    copyNumber(&one3, &empty);
    multiple(&one3, &empty, &power3);
    setNum(&item3, 1, 0);
    clearByZero(&arctan3);
    clearByZero(&tmp3);

    divide(&one, &num4, &one4);
    copyNumber(&one4, &empty);
    multiple(&one4, &empty, &power4);
    setNum(&item4, 1, 0);
    clearByZero(&arctan4);
    clearByZero(&tmp4);

    clearByZero(&number);
    clearByZero(&coefficient);
    clearByZero(pi);//計算したpiを格納

    while(item1.exp >= -(DECIMAL+1)/* && item5.exp >= -DECIMAL*3 && item8.exp >= -DECIMAL*3*/){
        if(denominator < 10) carry = 0;//有効数字調整
        else if(denominator < 100) carry = 1;
        else if(denominator < 1000) carry = 2;
        else carry = 3;
        setNum(&number, denominator, carry);//分母を格納(i+=1:denominator+=2)
        divide(&one, &number, &coefficient);//1/denominatorを格納

        //arctan(1/57)
        multiple(&coefficient, &one1, &item1);
        if(i % 2 == 0){//iが偶数のとき
            add(&arctan1, &item1, &empty);
            copyNumber(&empty, &arctan1);
        }
        else{//iが奇数のとき
            sub(&arctan1, &item1, &empty);
            copyNumber(&empty, &arctan1);
        }
        multiple(&one1, &power1, &empty);
        copyNumber(&empty, &one1);

        //arctan(1/239)
        if(item2.exp >= -(DECIMAL + 1)){//arctan(1/5)
            multiple(&coefficient, &one2, &item2);//{1/(2i+1)}*(1/5)^(2i+1)
            if(i % 2 == 0){//iが偶数のとき
                add(&arctan2, &item2, &empty);//arctan(1/5)を求める
                copyNumber(&empty, &arctan2);
            }
            else{//iが奇数のとき
                sub(&arctan2, &item2, &empty);//arctan(1/5)を求める
                copyNumber(&empty, &arctan2);
            }
            multiple(&one2, &power2, &empty);
            copyNumber(&empty, &one2);
        }

        //arctan(1/682)
        if(item3.exp >= -(DECIMAL + 1)){
            multiple(&coefficient, &one3, &item3);
            if(i % 2 == 0){//iが偶数のとき
                add(&arctan3, &item3, &empty);
                copyNumber(&empty, &arctan3);
            }
            else{//iが奇数のとき
                sub(&arctan3, &item3, &empty);
                copyNumber(&empty, &arctan3);
            }
            multiple(&one3, &power3, &empty);
            copyNumber(&empty, &one3);
        }

        //arctan(1/12943)
        if(item4.exp >= -(DECIMAL + 1)){
            multiple(&coefficient, &one4, &item4);
            if(i % 2 == 0){//iが偶数のとき
                add(&arctan4, &item4, &empty);
                copyNumber(&empty, &arctan4);
            }
            else{//iが奇数のとき
                sub(&arctan4, &item4, &empty);
                copyNumber(&empty, &arctan4);
            }
            multiple(&one4, &power4, &empty);
            copyNumber(&empty, &one4);
        }

        denominator += 2;
        i++;
    }


    multiple(&arctan1, &onesevensix, &tmp1);//176倍
    multiple(&arctan2, &twoeight, &tmp2);//28倍
    multiple(&arctan3, &foureight, &tmp3);//48倍
    multiple(&arctan4, &ninesix, &tmp4);//96倍
    add(&tmp1, &tmp2, pi);
    add(pi, &tmp4, &empty);
    sub(&empty, &tmp3, pi);//合計
}

void arctan(int a, struct NUMBER *arc){
    int denominator = 1;//分母を格納(初期:1)
    int carry = 0;//逆数のときに使う
    int i = 0;//for文で使う
    struct NUMBER one, num;//数字
    struct NUMBER onenum;//逆数
    struct NUMBER powernum;//2乗
    struct NUMBER itemnum;//係数
    struct NUMBER arctannum;//arctan
    struct NUMBER empty, number, coefficient;//その他
    clearByZero(&empty);//コピーのときとかに使う

    setNum(&one, 1, 0);//1.e0を格納
    if(a < 10) carry = 0;//有効数字調整
    else if(a < 100) carry = 1;
    else if(a < 1000) carry = 2;
    else if(a < 10000) carry = 3;
    else carry = 4;
    setNum(&num, a, carry);//a.ecarryを格納

    divide(&one, &num, &onenum);//(1/a)^(2i+1)を格納
    copyNumber(&onenum, &empty);
    multiple(&onenum, &empty, &powernum);//(1/a)^2を格納
    clearByZero(&itemnum);//{1/(2i+1)}*(1/a)^(2i+1)を格納
    clearByZero(&arctannum);//arctan(1/a)を格納

    clearByZero(&number);//1/aを格納
    clearByZero(&coefficient);//iのときの係数{1/(2i+1)}を格納
    clearByZero(arc);//計算結果を格納

    while(itemnum.exp >= -(DECIMAL+1)){
        if(denominator < 10) carry = 0;//有効数字調整
        else if(denominator < 100) carry = 1;
        else if(denominator < 1000) carry = 2;
        else carry = 3;
        setNum(&number, denominator, carry);//分母を格納(i+=1:denominator+=2)
        divide(&one, &number, &coefficient);//1/denominatorを格納

        //arctan(1/a)
        multiple(&coefficient, &onenum, &itemnum);//{1/(2i+1)}*(1/a)^(2i+1)
        if(i % 2 == 0){//iが偶数のとき
            add(&arctannum, &itemnum, &empty);//arctan(1/a)を求める
            copyNumber(&empty, &arctannum);
        }
        else{//iが奇数のとき
            sub(&arctannum, &itemnum, &empty);//arctan(1/a)を求める
            copyNumber(&empty, &arctannum);
        }
        multiple(&onenum, &powernum, &empty);
        copyNumber(&empty, &onenum);

        denominator += 2;//分母を2増やす
        i++;//nを増やす
    }

    copyNumber(&arctannum, arc);
}

int main(int argc, char **argv){
    double before = 0;//開始時の時間
    double after = 0;//終了時の時間
    struct NUMBER pi;//計算したpiを格納
    struct timeval time;
    gettimeofday(&time, NULL);
    before = (double)time.tv_sec + (double)time.tv_usec * 1.e-6;

    Dase(&pi);
    printf("KETA=%d\n", KETA);
    printf("pi=");
    dispNumber(&pi);
    printf("\n");

    gettimeofday(&time, NULL);
    after = (double)time.tv_sec + (double)time.tv_usec * 1.e-6;
    printf("time=%f\n", after - before);

    return 0;
}
