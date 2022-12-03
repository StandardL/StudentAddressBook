// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "MainWindow.xaml.h"
#if __has_include("MainWindow.g.cpp")
#include "MainWindow.g.cpp"
#endif
#pragma execution_character_set("utf-8")

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace std;


// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::__Final_StudentAddressBook::implementation
{
    int32_t MainWindow::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void MainWindow::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    //以树的形式输出二叉树
    void MainWindow::printBSTree_T()
    {
        printBSTree_T(root, "");
    }
    void MainWindow::printBSTree_T(BSTNode* ptr, string s)
    {
        if (ptr == NULL)
            return;
        else
        {
            printBSTree_T(ptr->right, s + "\t\t");
            result += s; //输出空格
            result = result + to_string(to_hstring(ptr->key)) + "\n";  //输出结点数据
            printBSTree_T(ptr->left, s + "\t\t");
        }
    }

    //插入学生
    bool MainWindow::Insert_recursion(int k, string na, string tele, string add, int gen, string d)
    {
        //根结点为空的情况
        if (root == NULL) {
            BSTNode* s = new BSTNode(k, na, tele, add, gen, d);
            root = s;
            return true;
        }
        //否则进入递归
        return Insert_recursion(k, na, tele, add, gen, d, root);
    }
    bool MainWindow::Insert_recursion(int k, string na, string tele, string add, int gen, string d, BSTNode*& ptr)
    {
        if (ptr == NULL) {
            BSTNode* s = new BSTNode(k, na, tele, add, gen, d);
            ptr = s;
            return true;
        }
        else if (ptr->key == k) {
            cout << "相同学号的学生信息已存在！\n";
            return false;
        }
        else if (k < ptr->key)	return Insert_recursion(k, na, tele, add, gen, d, ptr->left);
        else return Insert_recursion(k, na, tele, add, gen, d, ptr->right);
    }

    //递归删除结点
    bool MainWindow::Remove_recursion(int& x)
    {
        //s为缓存结点，p为需要删除的结点，p为需要删除的结点的父结点.
        BSTNode* s, * p, * pr;
        p = Search_recursion(x, root, pr);
        //如果找不到p，返回删除失败
        if (p == NULL)
            return false;
        if (p->left != NULL && p->right != NULL)  //结点有双子女
        {
            s = p->right; pr = p;  //找*p的中序后继*s
            while (s->left != NULL)
            {
                pr = s;
                s = s->left;
            }
            //用*s的值代替*p的值
            p->key = s->key;
            p->address = s->address;
            p->gender = s->gender;
            p->date = s->date;
            p->name = s->name;
            p->telephone = s->telephone;

            p = s;  //再删*s
        }
        if (p->right == NULL)  //左子树非空，记下左子树
            s = p->left;
        else  //否则记下右子树（可能为空）
            s = p->right;
        if (p == root)  //被删结点为根结点
            root = s;
        else if (pr->left == p)  //父结点直接链接子女结点
            pr->left = s;
        else
            pr->right = s;

        delete p;
        return true;
    }

    //从csv中读取
    bool MainWindow::readFromTxt()
    {
        ifstream inFile;
        inFile.open(pre_add+"\\students.csv", ios::in);
        if (!inFile) {
            //cout << "students.csv打开失败！请检查文件是否存在！\n";
            return false;
        }

        unsigned long long k; int gen;
        string na, tele, add, d;

        string line, field;
        getline(inFile, line);  //读取标题行
        //按行读取.
        while (getline(inFile, line)) {
            istringstream sin(line);//将整行字符串line读入到字符串流sin中
            //以制表符为分隔符读取
            // 
            //姓名
            getline(sin, field, ',');
            na = field;
            //学号
            getline(sin, field, ',');
            k = stoll(field);
            //地址
            getline(sin, field, ',');
            add = field;
            //出生日期
            getline(sin, field, ',');
            d = field;
            //性别
            getline(sin, field, ',');
            if (field == "女") gen = 0;
            else gen = 1;
            //电话号码
            getline(sin, field, ',');
            tele = field;

            //插入结点
            Insert_recursion(k, na, tele, add, gen, d);
        }
        inFile.close();
        return true;
    }

    //写出到csv文件中
    void MainWindow::writeToTxt()
    {
        ofstream os;
        //string desktop = getDesktopPath();
        os.open(pre_add + "\\students_output.csv", ios::out);

        //输出表头
        os << "姓名,学号,地址,生日,性别,电话号码" << endl;

        //中序遍历输出所有结点
        write_out(os);

        //cout << "输出成功！\n";
        os.close();
    }

    //前序遍历检查是否为二叉搜索树
    bool MainWindow::Check(BSTNode* p)
    {
        if (p->left != NULL && p->left->key > p->key)
            return false;
        else if (p->right != NULL && p->right->key < p->key)
            return false;
        else if (p->left == NULL && p->right == NULL)
            return true;
        else
        {
            bool tagl, tagr;
            tagl = tagr = true;
            if (p->left != NULL)
                tagl = Check(p->left);
            if (p->right != NULL)
                tagr = Check(p->right);
            if (tagl && tagr)  //均为真的时候
                return true;
            else
                return false;
        }
    }

    //中序遍历输出全部学生信息
    void MainWindow::InOrder(BSTNode* ptr)
    {
        if (NULL == ptr)
            return;

        InOrder(ptr->left);

        result += (ptr->name + "\t" + to_string(to_hstring(ptr->key)) + "\t" + ptr->address + "\t"+ ptr->date + "\t");

        if (ptr->gender == 0) {
            result += "女\t";
        }
        else {
            result += "男\t";
        }
        result += (ptr->telephone + "\n");

        InOrder(ptr->right);
    }

    //中序遍历把学生簿输出到文件中.
    void MainWindow::write_out(BSTNode* ptr, std::ofstream& outFile)
    {
        if (NULL == ptr)
            return;

        write_out(ptr->left, outFile);

        outFile << ptr->name << "," << ptr->key << "," << ptr->address << ","
            << ptr->date << ",";
        if (ptr->gender == 0) outFile << "女";
        else outFile << "男";
        outFile << "," << ptr->telephone << endl;

        write_out(ptr->right, outFile);
    }

    //递归方法搜索x
    MainWindow::BSTNode* MainWindow::Search_recursion(int x, BSTNode* ptr, BSTNode*& pr)
    {
        if (ptr == NULL)
            return NULL;
        else if (x < ptr->key) {
            pr = ptr;
            return Search_recursion(x, ptr->left, pr);
        }
        else if (x > ptr->key) {
            pr = ptr;
            return Search_recursion(x, ptr->right, pr);
        }
        return ptr;
    }


    

}


//创建按钮
void winrt::__Final_StudentAddressBook::implementation::MainWindow::Create_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    //nums_content().ShowAsync();
    
}

//插入按钮
void winrt::__Final_StudentAddressBook::implementation::MainWindow::Insert_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    //初始化按钮
    insert_content().IsPrimaryButtonEnabled(false);
    insert_content().ShowAsync();
}

//打印按钮
void winrt::__Final_StudentAddressBook::implementation::MainWindow::Print_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    InOrder();

    string text = title + result;

    output_textbox().Text(to_hstring(text));
    infobar_main().Title(L"成功");
    infobar_main().Message(L"请留意左侧输出区域的输出信息");
    infobar_main().Severity(success_info().Severity());
    infobar_main().IsOpen(true);
}

//删除按钮
void winrt::__Final_StudentAddressBook::implementation::MainWindow::Delete_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    //初始化弹窗
    delete_content().IsPrimaryButtonEnabled(false);
    delete_content().ShowAsync();
}

//退出按钮
void winrt::__Final_StudentAddressBook::implementation::MainWindow::Exit_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    //强行崩溃退出
    Application().Current().Exit();
}

//查询按钮
void winrt::__Final_StudentAddressBook::implementation::MainWindow::Search_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    search_content().IsPrimaryButtonEnabled(false);
    search_content().ShowAsync();
}

//写出按钮
void winrt::__Final_StudentAddressBook::implementation::MainWindow::Write_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    string succ_text = "写出成功！";
    string fail_text = "写出失败！请检查本机桌面目录下是否存在students.csv";

    writeToTxt();
    //提示bar
    infobar_main().Title(L"成功");
    infobar_main().Message(L"写出成功！导出文件在桌面的Students_Address_Book文件夹内students.csv中");
    infobar_main().Severity(success_info().Severity());
    infobar_main().IsOpen(true);
    //弹窗
    write_text().Text(to_hstring(succ_text));
    write_content().ShowAsync();
}

//读取按钮
void winrt::__Final_StudentAddressBook::implementation::MainWindow::Read_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    hstring succ_text = L"读取成功！";
    hstring fail_text = L"读取失败！请检查本机\"C:\\Students(WinUI3)\"目录下是否存在students.csv";

    if (readFromTxt())
    {
        //提示bar
        infobar_main().Title(L"成功");
        infobar_main().Message(succ_text);
        infobar_main().Severity(success_info().Severity());
        infobar_main().IsOpen(true);
        //弹窗
        read_text().Text(succ_text);
    }
    else
    {
        //提示bar
        infobar_main().Title(L"失败");
        infobar_main().Message(fail_text);
        infobar_main().Severity(success_info().Severity());
        infobar_main().IsOpen(true);
        //弹窗
        read_text().Text(fail_text);
    }

    read_content().ShowAsync();
}

//插入弹窗的确定按钮
void winrt::__Final_StudentAddressBook::implementation::MainWindow::insert_content_PrimaryButtonClick(winrt::Microsoft::UI::Xaml::Controls::ContentDialog const& sender, winrt::Microsoft::UI::Xaml::Controls::ContentDialogButtonClickEventArgs const& args)
{
    int key = stoi(to_string(insert_key().Text()));
    string name = to_string(insert_name().Text());
    string gender = to_string(insert_gender().Text());
    auto tele = to_string(insert_tele().Text());
    auto add = to_string(insert_address().Text());
    auto birth = to_string(insert_birth().Text());
    int gen;
    if (gender == "男")
        gen = 1;
    else
        gen = 0;
    bool isInsertSucc = Insert_recursion(key, name, tele, add, gen, birth);
    if (isInsertSucc)
    {
        infobar_main().Severity(success_info().Severity());
        infobar_main().Title(L"插入成功");
        infobar_main().Message(L"请再次点击打印信息按钮刷新输出信息");
        infobar_main().IsOpen(true);
    }
    else
    {
        infobar_main().Severity(fail_info().Severity());
        infobar_main().Title(L"插入失败");
        infobar_main().Message(L"在学生通讯录中存在相同学号的学生");
        infobar_main().IsOpen(true);
    }
}

//插入弹窗的取消按钮
void winrt::__Final_StudentAddressBook::implementation::MainWindow::insert_content_CloseButtonClick(winrt::Microsoft::UI::Xaml::Controls::ContentDialog const& sender, winrt::Microsoft::UI::Xaml::Controls::ContentDialogButtonClickEventArgs const& args)
{
    infobar_main().Title(L"警告");
    infobar_main().Message(L"您刚才点击了取消插入，没有任何新信息被插入到学生通讯录中");
    infobar_main().Severity(warning_info().Severity());
    infobar_main().IsOpen(true);
}

//插入弹框的文本发生改变
void winrt::__Final_StudentAddressBook::implementation::MainWindow::insert_TextChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Controls::TextChangedEventArgs const& e)
{
    check_insert();
}

//取消删除的按钮被按下
void winrt::__Final_StudentAddressBook::implementation::MainWindow::delete_content_CloseButtonClick(winrt::Microsoft::UI::Xaml::Controls::ContentDialog const& sender, winrt::Microsoft::UI::Xaml::Controls::ContentDialogButtonClickEventArgs const& args)
{
    infobar_main().Title(L"警告");
    infobar_main().Message(L"您刚才点击了取消删除，没有任何学生信息被删除");
    infobar_main().Severity(warning_info().Severity());
    infobar_main().IsOpen(true);
}

//确定删除的按钮被按下
void winrt::__Final_StudentAddressBook::implementation::MainWindow::delete_content_PrimaryButtonClick(winrt::Microsoft::UI::Xaml::Controls::ContentDialog const& sender, winrt::Microsoft::UI::Xaml::Controls::ContentDialogButtonClickEventArgs const& args)
{
    int key = stoi(to_string(delete_key().Text()));
    bool isRemoveSucc = winrt::__Final_StudentAddressBook::implementation::MainWindow::Remove_recursion(key);
    if (isRemoveSucc)
    {
        infobar_main().Severity(success_info().Severity());
        infobar_main().Title(L"删除成功");
        infobar_main().Message(L"请再次点击打印信息按钮刷新输出信息");
        infobar_main().IsOpen(true);
    }
    else
    {
        infobar_main().Severity(fail_info().Severity());
        infobar_main().Title(L"删除失败");
        infobar_main().Message(L"在学生通讯录中没有查询到该学号对应的学生");
        infobar_main().IsOpen(true);
    }
    
}

//插入文本框的确认按钮
void winrt::__Final_StudentAddressBook::implementation::MainWindow::check_insert()
{
    auto name = to_string(insert_name().Text());
    auto key = to_string(insert_key().Text());
    auto tele = to_string(insert_tele().Text());
    auto add = to_string(insert_address().Text());
    auto gender = to_string(insert_gender().Text());
    auto birth = to_string(insert_birth().Text());
    string empty = "";

    //当文本框有内容时 确定按钮可用  否则禁用
    if (name != empty && key != empty && tele != empty && add != empty && gender != empty && birth != empty)
        insert_content().IsPrimaryButtonEnabled(true);
    else
        insert_content().IsPrimaryButtonEnabled(false);
}

//string winrt::__Final_StudentAddressBook::implementation::MainWindow::getDesktopPath()
//{
//    
//}

//删除弹框的文本发生改变
void winrt::__Final_StudentAddressBook::implementation::MainWindow::delete_key_TextChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Controls::TextChangedEventArgs const& e)
{
    //逻辑类似上述过程 当文本框有内容时 确定按钮可用 否则禁用
    auto key = to_string(delete_key().Text());
    string empty = "";
    if (key != empty)
        delete_content().IsPrimaryButtonEnabled(true);
    else
        delete_content().IsPrimaryButtonEnabled(false);
}

//查询弹窗的取消按钮
void winrt::__Final_StudentAddressBook::implementation::MainWindow::search_content_CloseButtonClick(winrt::Microsoft::UI::Xaml::Controls::ContentDialog const& sender, winrt::Microsoft::UI::Xaml::Controls::ContentDialogButtonClickEventArgs const& args)
{
    infobar_main().Severity(warning_info().Severity());
    infobar_main().Title(L"查询取消");
    infobar_main().Message(L"您刚才点击了取消查询");
}

//查询弹窗的确定按钮
void winrt::__Final_StudentAddressBook::implementation::MainWindow::search_content_PrimaryButtonClick(winrt::Microsoft::UI::Xaml::Controls::ContentDialog const& sender, winrt::Microsoft::UI::Xaml::Controls::ContentDialogButtonClickEventArgs const& args)
{
    auto key = stoll(to_string(search_key().Text()));
    winrt::__Final_StudentAddressBook::implementation::MainWindow::BSTNode* pr, *res;

    res = winrt::__Final_StudentAddressBook::implementation::MainWindow::Search_recursion(key, root, pr);
    if (res != NULL) //查询成功
    {
        result = "";  //清空输出string串
        result += (res->name + "\t" + to_string(to_hstring(res->key)) + "\t" + res->address + "\t" + res->date + "\t");
        if (res->gender == 0)
            result += "女\t";
        else
            result += "男\t";
        result += (res->telephone + "\n");

        hstring final_text = to_hstring(title + result);
        output_textbox().Text(final_text);
        infobar_main().Severity(success_info().Severity());
        infobar_main().Title(L"查询成功");
        infobar_main().Message(L"请查看左侧输出框的内容");
    }
    else
    {
        output_textbox().Text(L"");
        infobar_main().Severity(fail_info().Severity());
        infobar_main().Title(L"查询失败");
        infobar_main().Message(L"在学生通讯录中没有查询到该学号对应的学生");
    }
}

//查询弹框的文本发生改变
void winrt::__Final_StudentAddressBook::implementation::MainWindow::search_key_TextChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Controls::TextChangedEventArgs const& e)
{
    auto empty = L"";
    auto key = search_key().Text();
    if (key != empty)
        search_content().IsPrimaryButtonEnabled(true);
    else
        search_content().IsPrimaryButtonEnabled(false);
}

//取消新建按钮被按下
void winrt::__Final_StudentAddressBook::implementation::MainWindow::create_content_CloseButtonClick(winrt::Microsoft::UI::Xaml::Controls::ContentDialog const& sender, winrt::Microsoft::UI::Xaml::Controls::ContentDialogButtonClickEventArgs const& args)
{

}

//确定新建按钮被按下
void winrt::__Final_StudentAddressBook::implementation::MainWindow::create_content_PrimaryButtonClick(winrt::Microsoft::UI::Xaml::Controls::ContentDialog const& sender, winrt::Microsoft::UI::Xaml::Controls::ContentDialogButtonClickEventArgs const& args)
{
    
}

//创建文本框的内容发生改变
void winrt::__Final_StudentAddressBook::implementation::MainWindow::create_TextChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Controls::TextChangedEventArgs const& e)
{
    
}

////创建数量文本框的内容发生改变
//void winrt::__Final_StudentAddressBook::implementation::MainWindow::create_nums_TextChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Controls::TextChangedEventArgs const& e)
//{
//
//}

////取消创建数量按钮
//void winrt::__Final_StudentAddressBook::implementation::MainWindow::nums_content_CloseButtonClick(winrt::Microsoft::UI::Xaml::Controls::ContentDialog const& sender, winrt::Microsoft::UI::Xaml::Controls::ContentDialogButtonClickEventArgs const& args)
//{
//
//}
//
////确定创建数量按钮
//void winrt::__Final_StudentAddressBook::implementation::MainWindow::nums_content_PrimaryButtonClick(winrt::Microsoft::UI::Xaml::Controls::ContentDialog const& sender, winrt::Microsoft::UI::Xaml::Controls::ContentDialogButtonClickEventArgs const& args)
//{
//    //create_content().ShowAsync();
//}

//创建一个样板
void winrt::__Final_StudentAddressBook::implementation::MainWindow::Button_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    
    ofstream os;
    string temp = pre_add;

    os.open(pre_add + "\\demo.csv", ios::out);

    if (!os)
        infobar_main().Message(L"样板生成失败！");

    //输出表头
    os << "姓名,学号,地址,生日,性别,电话号码\n";

    //中序遍历输出所有结点
    os << "测试," << 114514 << ",霓虹," << "1914.11.4," << "男," << "13456\n";

    //cout << "输出成功！\n";
    os.close();

    infobar_main().Title(L"样板已生成");
    infobar_main().Message(L"请查看C:\\Students(WinUI3)的demo.csv文件，如遇乱码请手动使用记事本打开并另存为ANSI编码。");
    infobar_main().Severity(warning_info().Severity());
    infobar_main().IsOpen(true);
}
