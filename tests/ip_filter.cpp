#include <gtest/gtest.h>

#include "ip_filter/ip_filter.hpp"

using v_str = std::vector<std::string>;

TEST(ip_filter, check__func)
{
  std::vector<pr::ip_filter::ip> pool {
    pr::ip_filter::ip{v_str{"185","69","186","168"}},
    pr::ip_filter::ip{v_str{"157","39","22","224"}},
    pr::ip_filter::ip{v_str{"113","162","145","156"}},
    pr::ip_filter::ip{v_str{"85","254","10","197"}},
    pr::ip_filter::ip{v_str{"79","180","73","190"}},
    pr::ip_filter::ip{v_str{"71","223","241","223"}},
    pr::ip_filter::ip{v_str{"71","223","241","223"}},
    pr::ip_filter::ip{v_str{"67","232","81","208"}},
    pr::ip_filter::ip{v_str{"46","70","215","189"}},
    pr::ip_filter::ip{v_str{"1","146","145","4"}},
    pr::ip_filter::ip{v_str{"1","102","46","135"}},
    pr::ip_filter::ip{v_str{"1","29","168","152"}},
    pr::ip_filter::ip{v_str{"1","146","145","4"}},
    pr::ip_filter::ip{v_str{"1","102","46","135"}},
    pr::ip_filter::ip{v_str{"1","29","168","152"}},
    pr::ip_filter::ip{v_str{"46","70","215","189"}},
    pr::ip_filter::ip{v_str{"46","70","215","189"}},
    pr::ip_filter::ip{v_str{"1","102","46","135"}}
  };

  ASSERT_EQ(pr::ip_filter::process(), pool);
}
