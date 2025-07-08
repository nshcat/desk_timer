
#pragma once

#include <stm32g0b1xx.h>

#include "base.hxx"

namespace hal
{
    namespace gpio
    {
        namespace impl
        {
            class gpio_builder
            {
                gpio_builder(GPIO_TypeDef* gpiotd) {}
            };
        }

        class gpio
        {
            friend class impl::gpio_builder;

        protected:
            gpio(GPIO_TypeDef* gpiotd) : m_gpiotd(gpiotd) {}

        protected:
            GPIO_TypeDef* m_gpiotd{};
        };
    }
}
