// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "MainWindow.g.h"

namespace winrt
{
    namespace MUC = Microsoft::UI::Composition;
    namespace MUCSB = Microsoft::UI::Composition::SystemBackdrops;
    namespace MUX = Microsoft::UI::Xaml;
    namespace WS = Windows::System;
}
using std::string;

namespace winrt::__Final_StudentAddressBook::implementation
{
    //Using Mica Material
    struct MainWindow : MainWindowT<MainWindow>
    {
        winrt::MUCSB::SystemBackdropConfiguration m_configuration{ nullptr };
        winrt::MUCSB::MicaController m_backdropController{ nullptr };
        winrt::MUX::Window::Activated_revoker m_activatedRevoker;
        winrt::MUX::Window::Closed_revoker m_closedRevoker;
        winrt::MUX::FrameworkElement::ActualThemeChanged_revoker m_themeChangedRevoker;
        winrt::MUX::FrameworkElement m_rootElement{ nullptr };
        winrt::WS::DispatcherQueueController m_dispatcherQueueController{ nullptr };

        MainWindow()
        {
            InitializeComponent();

            SetBackground();

            Title(L"学生通讯录(WinUI3)");

            m_closedRevoker = this->Closed(winrt::auto_revoke, [&](auto&&, auto&&)
                {
                    if (nullptr != m_backdropController)
                    {
                        m_backdropController.Close();
                        m_backdropController = nullptr;
                    }

            if (nullptr != m_dispatcherQueueController)
            {
                m_dispatcherQueueController.ShutdownQueueAsync();
                m_dispatcherQueueController = nullptr;
            }
                });

           // //Resize window
           // winrt::Windows::Graphics::SizeInt32 windowSize;
           // windowSize.Height = 1280;
           // windowSize.Width = 720;

           ///* Window window = e.Parameter().as<Window>();
           // MainWindow mainWindow = window.as<MainWindow>();
           // AppWindow appWindow = mainWindow.MyAppWindow();
           // m_mainAppWindow = appWindow;*/
        }

        void SetBackground()
        {
            if (winrt::MUCSB::MicaController::IsSupported())
            {
                // We ensure that there is a Windows.System.DispatcherQueue on the current thread.
                // Always check if one already exists before attempting to create a new one.
                if (nullptr == winrt::WS::DispatcherQueue::GetForCurrentThread() &&
                    nullptr == m_dispatcherQueueController)
                {
                    m_dispatcherQueueController = CreateSystemDispatcherQueueController();
                }

                // Setup the SystemBackdropConfiguration object.
                SetupSystemBackdropConfiguration();

                // Setup Mica on the current Window.
                m_backdropController = winrt::MUCSB::MicaController();
                m_backdropController.SetSystemBackdropConfiguration(m_configuration);
                m_backdropController.AddSystemBackdropTarget(
                    this->try_as<winrt::MUC::ICompositionSupportsSystemBackdrop>());
            }
            else
            {
                // The backdrop material is not supported.
            }
        }

        winrt::WS::DispatcherQueueController CreateSystemDispatcherQueueController()
        {
            DispatcherQueueOptions options
            {
                sizeof(DispatcherQueueOptions),
                DQTYPE_THREAD_CURRENT,
                DQTAT_COM_NONE
            };

            ::ABI::Windows::System::IDispatcherQueueController* ptr{ nullptr };
            winrt::check_hresult(CreateDispatcherQueueController(options, &ptr));
            return { ptr, take_ownership_from_abi };
        }

        void SetupSystemBackdropConfiguration()
        {
            m_configuration = winrt::MUCSB::SystemBackdropConfiguration();

            // Activation state.
            m_activatedRevoker = this->Activated(winrt::auto_revoke,
                [&](auto&&, MUX::WindowActivatedEventArgs const& args)
                {
                    m_configuration.IsInputActive(
                        winrt::MUX::WindowActivationState::Deactivated != args.WindowActivationState());
                });

            // Initial state.
            m_configuration.IsInputActive(true);

            // Application theme.
            m_rootElement = this->Content().try_as<winrt::MUX::FrameworkElement>();
            if (nullptr != m_rootElement)
            {
                m_themeChangedRevoker = m_rootElement.ActualThemeChanged(winrt::auto_revoke,
                    [&](auto&&, auto&&)
                    {
                        m_configuration.Theme(
                            ConvertToSystemBackdropTheme(m_rootElement.ActualTheme()));
                    });

                // Initial state.
                m_configuration.Theme(
                    ConvertToSystemBackdropTheme(m_rootElement.ActualTheme()));
            }
        }

        winrt::MUCSB::SystemBackdropTheme ConvertToSystemBackdropTheme(
            winrt::MUX::ElementTheme const& theme)
        {
            switch (theme)
            {
            case winrt::MUX::ElementTheme::Dark:
                return winrt::MUCSB::SystemBackdropTheme::Dark;
            case winrt::MUX::ElementTheme::Light:
                return winrt::MUCSB::SystemBackdropTheme::Light;
            default:
                return winrt::MUCSB::SystemBackdropTheme::Default;
            }
        }
        //End of Mica Definition
        
        


        int32_t MyProperty();
        void MyProperty(int32_t value);

       

        void Create_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void Insert_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void Print_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void Delete_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void Exit_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void Search_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void Write_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void Read_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void insert_content_PrimaryButtonClick(winrt::Microsoft::UI::Xaml::Controls::ContentDialog const& sender, winrt::Microsoft::UI::Xaml::Controls::ContentDialogButtonClickEventArgs const& args);
        void insert_content_CloseButtonClick(winrt::Microsoft::UI::Xaml::Controls::ContentDialog const& sender, winrt::Microsoft::UI::Xaml::Controls::ContentDialogButtonClickEventArgs const& args);
        void insert_TextChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Controls::TextChangedEventArgs const& e);
        void delete_content_CloseButtonClick(winrt::Microsoft::UI::Xaml::Controls::ContentDialog const& sender, winrt::Microsoft::UI::Xaml::Controls::ContentDialogButtonClickEventArgs const& args);
        void delete_content_PrimaryButtonClick(winrt::Microsoft::UI::Xaml::Controls::ContentDialog const& sender, winrt::Microsoft::UI::Xaml::Controls::ContentDialogButtonClickEventArgs const& args);
        void delete_key_TextChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Controls::TextChangedEventArgs const& e);
        void search_content_CloseButtonClick(winrt::Microsoft::UI::Xaml::Controls::ContentDialog const& sender, winrt::Microsoft::UI::Xaml::Controls::ContentDialogButtonClickEventArgs const& args);
        void search_content_PrimaryButtonClick(winrt::Microsoft::UI::Xaml::Controls::ContentDialog const& sender, winrt::Microsoft::UI::Xaml::Controls::ContentDialogButtonClickEventArgs const& args);
        void search_key_TextChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Controls::TextChangedEventArgs const& e);
        void create_content_CloseButtonClick(winrt::Microsoft::UI::Xaml::Controls::ContentDialog const& sender, winrt::Microsoft::UI::Xaml::Controls::ContentDialogButtonClickEventArgs const& args);
        void create_content_PrimaryButtonClick(winrt::Microsoft::UI::Xaml::Controls::ContentDialog const& sender, winrt::Microsoft::UI::Xaml::Controls::ContentDialogButtonClickEventArgs const& args);
        void create_TextChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Controls::TextChangedEventArgs const& e);
        //void create_nums_TextChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Controls::TextChangedEventArgs const& e);
        //void nums_content_CloseButtonClick(winrt::Microsoft::UI::Xaml::Controls::ContentDialog const& sender, winrt::Microsoft::UI::Xaml::Controls::ContentDialogButtonClickEventArgs const& args);
        //void nums_content_PrimaryButtonClick(winrt::Microsoft::UI::Xaml::Controls::ContentDialog const& sender, winrt::Microsoft::UI::Xaml::Controls::ContentDialogButtonClickEventArgs const& args);
        void Button_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);


        //自定义函数
        void check_insert();//控制确定按钮是否可按
        //string getDesktopPath()  //获取桌面绝对路径.
        //{
        //    char szDir[1000];
        //    if (SHGetSpecialFolderPathA(HWND_DESKTOP, szDir, CSIDL_DESKTOP, FALSE))
        //        return string(szDir);
        //    else
        //        return "Error";
        //}
        

        //二叉搜索树
        struct BSTNode  //二叉树结点
        {
            unsigned long long key;  //学号
            string name;  //姓名
            string date;  //出生日期
            int gender;  //性别，女为0，男为1
            string telephone;  //电话
            string address;  //地址

            BSTNode* left, * right;  //左右子女

            BSTNode() //无参构造函数
            {
                left = right = NULL;
                key = 0;
                name = "-";
                gender = -1;
                name = "无名氏";
                telephone = "-";
                address = "-";
            }
            BSTNode(int k, string na, string tele, string add, int gen, string d)  //带参构造函数
            {
                key = k; name = na; telephone = tele; address = add; gender = gen; date = d;
                left = right = NULL;
            }
            ~BSTNode() {}  //析构函数
        };

        string title = "姓名\t学号\t地址\t生日\t\t性别\t电话\n";
        string result = "";
        string pre_add = "C:\\Students(WinUI3)";

        BSTNode* root;													                                    //根结点
        void printBSTree_T(BSTNode* t, string s);						                                                        //以树的形式输出二叉树
        bool Insert_recursion(int k, string na, string tele, string add, int gen, string d, BSTNode*& ptr);						//递归的方式插入新元素
        bool Check(BSTNode* p);											                                                        //检查是否为二叉搜索树
        void InOrder(BSTNode* ptr);										                                                        //中序遍历输出全部学生信息
        void write_out(BSTNode* ptr, std::ofstream& outFile);                                                                   //中序遍历写出文件

        BSTNode* Search_recursion(int x, BSTNode* ptr, BSTNode*& pr);	                                                        //递归的方式搜索x(在通讯录中查询学生信息)
        void printBSTree_T();											                                                        //以树的形式输出二叉树
        bool Insert_recursion(int k, string na, string tele, string add, int gen, string d);									//递归的方式插入新元素
        bool Remove_recursion(int& x);									                                                        //删除递归算法
        bool check() { return Check(root); }							                                                        //检查是否为二叉搜索树
        void InOrder() {
            result = "";
            InOrder(root); }								                                                        //中序遍历输出全部学生信息
        BSTNode* getRoot() { return root; }
        void write_out(std::ofstream& outFile) { write_out(root, outFile); }

        //void menu();		//操作菜单
        //void create();		//创建二叉搜索树学生通讯录样板
        //void insert();		//向学生通讯录插入学生信息
        //void search();		//查找学生信息
        //void mydelete();	//在通讯录删除学生信息
        bool readFromTxt();	//从文件中读取通讯录信息
        void writeToTxt();	//向文件写入学生通讯录信息

        
    };
}

namespace winrt::__Final_StudentAddressBook::factory_implementation
{
    struct MainWindow : MainWindowT<MainWindow, implementation::MainWindow>
    {
    };
}
