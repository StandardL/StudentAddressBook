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
};
}

namespace winrt::__Final_StudentAddressBook::factory_implementation
{
    struct MainWindow : MainWindowT<MainWindow, implementation::MainWindow>
    {
    };
}
