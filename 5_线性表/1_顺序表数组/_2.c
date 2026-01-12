//-----------------------------------------------------------------------------------------------------


#include<stdio.h>
#include<malloc.h>

struct DongShuZu {
  int* pShuZUTou;           //首地址
  unsigned int iRongLiang;  //容量
  unsigned int iShuLiang;   //已存储的数量
};

void ChuShiHua (struct DongShuZu* pSTShuzu);
void ZhenJia (struct DongShuZu* pSTShuzu, int iShuJu);
void ShuChu(struct DongShuZu* pStShuzu);
void ZengJiaZhong(struct DongShuZu* pSTShuzu, int iShuJu, int iXiaBiao);
void ZhengJiaKongJian(struct DongShuZu* pSTShuzu);

int main() {
  struct DongShuZu stshuzu;
  // 初始化
  ChuShiHua(&stshuzu);
  // 添加数据
  ZhenJia(&stshuzu,3);
  ZhenJia(&stshuzu,3);
  ZhenJia(&stshuzu,3);
  ZhenJia(&stshuzu,3);
  ZhenJia(&stshuzu,3);  // 此时调用zhengjia,容量还是4
  ZhenJia(&stshuzu,3);
  ZengJiaZhong(&stshuzu,6,2);

  ShuChu(&stshuzu);

  free(stshuzu.pShuZUTou);
  return 0;
}

// 动态数组初始化
void ChuShiHua (struct DongShuZu* pSTShuzu) {
  pSTShuzu->iRongLiang = 5;
  pSTShuzu->pShuZUTou = (int*)malloc(sizeof(int)*pSTShuzu->iRongLiang);
  pSTShuzu->iShuLiang = 0;
}

//动态尾添加元素
void ZhenJia (struct DongShuZu* pSTShuzu, int iShuJu) {
  //封装
  ZhengJiaKongJian(pSTShuzu);
  //将新数据装进去
  pSTShuzu->pShuZUTou[pSTShuzu->iShuLiang] = iShuJu;  //容量==下一个的下标
  //已数量变大
  pSTShuzu->iShuLiang++;
}
// 输出
void ShuChu(struct DongShuZu* pStShuzu) {
  if (NULL == pStShuzu) {
    printf("参数错误");  // 先保证指针有效
    return;
  }
  printf("容量:%u,数量:%u\n",pStShuzu->iRongLiang,pStShuzu->iShuLiang);
  for (unsigned int i = 0; i < pStShuzu->iShuLiang; i++) {
    printf("%d ",pStShuzu->pShuZUTou[i]);
  }
}

void ZengJiaZhong(struct DongShuZu* pSTShuzu, int iShuJu, int iXiaBiao) {
  if (NULL == pSTShuzu /*|| iXiaBiao+1 >= pSTShuzu->iShuLiang*/) {
    printf("参数错误");
    return;
  }
  //封装
  ZhengJiaKongJian(pSTShuzu);
  //如果下标太大,插入队尾
  if (iXiaBiao > pSTShuzu->iShuLiang) {
    iXiaBiao = pSTShuzu->iShuLiang;  // 让下标为最后一个
  }
  //向后挪
  for (unsigned int i = pSTShuzu->iShuLiang; i >iXiaBiao; i--) {
    pSTShuzu->pShuZUTou[i] = pSTShuzu->pShuZUTou[i-1];
  }
  //插入数据
  pSTShuzu->pShuZUTou[iXiaBiao] = iShuJu;
  //数量加一
  pSTShuzu->iShuLiang++;
}

void ZhengJiaKongJian(struct DongShuZu* pSTShuzu) {
  if (NULL == pSTShuzu) {
    return;
  }
  //判断满没满
  if (pSTShuzu->iRongLiang == pSTShuzu->iShuLiang) {
    //容量变大
    pSTShuzu->iRongLiang += 5;
    //申请空间
    int* pTemp = (int*)malloc(sizeof(int)*pSTShuzu->iRongLiang);
    //将原数据复制到新空间
    for (unsigned int i = 0; i < pSTShuzu->iShuLiang; i++) {
      pTemp[i] = pSTShuzu->pShuZUTou[i];
    }
    //将原空间释放
    free(pSTShuzu->pShuZUTou);
    //将数组头指向新空间
    pSTShuzu->pShuZUTou = pTemp;
  }
}