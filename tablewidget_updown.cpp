#include "tablewidget_updown.h"

tablewidget_updown::tablewidget_updown(QWidget *parent) : QTableWidget(parent)
{
    // 测试
    this->setColumnCount(2);//设置列数2
    this->setHorizontalHeaderLabels(QStringList() << QStringLiteral("1") << QStringLiteral("2"));
    this->insertRow(0);
    this->setItem(0,0,new QTableWidgetItem(QStringLiteral("a")));
    this->setItem(0,1,new QTableWidgetItem(QStringLiteral("aa")));
    this->insertRow(0);
    this->setItem(0,0,new QTableWidgetItem(QStringLiteral("b")));
    this->setItem(0,1,new QTableWidgetItem(QStringLiteral("bb")));
    this->insertRow(0);
    this->setItem(0,0,new QTableWidgetItem(QStringLiteral("c")));
    this->setItem(0,1,new QTableWidgetItem(QStringLiteral("cc")));

    // 拖拽设置
    this->setDragDropMode(QAbstractItemView::InternalMove);  // 内部移动
    this->setDropIndicatorShown(true);  // drop位置 提示
    this->setSelectionBehavior(QAbstractItemView::SelectRows);
}
/*
 * 2021.7.6 by gy
 * 拖拽 继承QTableWidget overwrite dropEvent事件
 * 功能：拖动一行到鼠标落下的位置
 * 注意：DragDropMode相关参数的设置
*/
void tablewidget_updown::dropEvent(QDropEvent *event)
{
    qDebug()<<"dropEvent";
    // 原行号与目标行号的确定
    int row_src,row_dst;
    row_src = this->currentRow();                        // 原行号 可加if
    QTableWidgetItem *item = this->itemAt(event->pos()); // 获取落点的item
    if(item !=nullptr){                                        // 判断是否为空
        row_dst = item->row();                                 // 不为空 获取其行号
        // 保证鼠标落下的位置 就是拖拽的一行最后所移动到的位置(考虑插入新行 移除原行的上下变化)
        row_src = (row_src > row_dst?    row_src + 1:row_src); // 如果src在dst的下方(行号大)，后续插入dst会影响src的行号
        row_dst = (row_src < row_dst?    row_dst + 1:row_dst); // 如果src在dst的上方(行号小)，后续移除src会影响dst的行号
        this->insertRow(row_dst);                              // 插入一行
    }
    else{                          // 落点没有item 说明拖动到了最下面
        row_dst = this->rowCount();// 获取行总数
        this->insertRow(row_dst);  // 在最后新增一行
    }
    // 执行移动 并移除原行
    for(int i = 0;i < this->columnCount();i++){            // 遍历列
        this->setItem(row_dst,i,this->takeItem(row_src,i));// 每一列item的移动
    }
    this->removeRow(row_src);                              // 删除原行
}
