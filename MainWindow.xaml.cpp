// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "MainWindow.xaml.h"
#if __has_include("MainWindow.g.cpp")
#include "MainWindow.g.cpp"
#endif
//#include "InsertDialog.xaml.h"

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

}


//创建按钮
void winrt::__Final_StudentAddressBook::implementation::MainWindow::Create_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    nums_content().ShowAsync();
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
    string succ_text = "读取成功！";
    string fail_text = "读取失败！请检查本机桌面目录下是否存在students.csv";

    //提示bar
    infobar_main().Title(L"成功");
    infobar_main().Message(L"读取成功！");
    infobar_main().Severity(success_info().Severity());
    infobar_main().IsOpen(true);
    //弹窗
    read_text().Text(to_hstring(succ_text));


    read_content().ShowAsync();
}

//插入弹窗的确定按钮
void winrt::__Final_StudentAddressBook::implementation::MainWindow::insert_content_PrimaryButtonClick(winrt::Microsoft::UI::Xaml::Controls::ContentDialog const& sender, winrt::Microsoft::UI::Xaml::Controls::ContentDialogButtonClickEventArgs const& args)
{

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

}

//查询弹窗的确定按钮
void winrt::__Final_StudentAddressBook::implementation::MainWindow::search_content_PrimaryButtonClick(winrt::Microsoft::UI::Xaml::Controls::ContentDialog const& sender, winrt::Microsoft::UI::Xaml::Controls::ContentDialogButtonClickEventArgs const& args)
{

}

//查询弹框的文本发生改变
void winrt::__Final_StudentAddressBook::implementation::MainWindow::search_key_TextChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Controls::TextChangedEventArgs const& e)
{

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

//创建数量文本框的内容发生改变
void winrt::__Final_StudentAddressBook::implementation::MainWindow::create_nums_TextChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Controls::TextChangedEventArgs const& e)
{

}

//取消创建数量按钮
void winrt::__Final_StudentAddressBook::implementation::MainWindow::nums_content_CloseButtonClick(winrt::Microsoft::UI::Xaml::Controls::ContentDialog const& sender, winrt::Microsoft::UI::Xaml::Controls::ContentDialogButtonClickEventArgs const& args)
{

}

//确定创建数量按钮
void winrt::__Final_StudentAddressBook::implementation::MainWindow::nums_content_PrimaryButtonClick(winrt::Microsoft::UI::Xaml::Controls::ContentDialog const& sender, winrt::Microsoft::UI::Xaml::Controls::ContentDialogButtonClickEventArgs const& args)
{
    create_content().ShowAsync();
}
