#include "gtest/gtest.h"
#include "smesh/config/config.h"
#include <QtVariantPropertyManager>

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

TEST(PropertyDef, Construtor)
{
  smesh::PropertyDef def_0;
  EXPECT_TRUE(!def_0.IsValid());
  smesh::PropertyDef def_1(QVariant::Int);
  EXPECT_TRUE(def_1.IsValid());
  EXPECT_TRUE(def_1.type() == QVariant::Int);
}

TEST(PropertyDef, SetValue)
{
  smesh::PropertyDef def(QVariant::Double);
  EXPECT_EQ(def.type(), QVariant::Double);
  def.set_default_value(0.5);
  EXPECT_DOUBLE_EQ(def.default_value().toDouble(), 0.5);
  def.set_max(10.0);
  def.set_min(0.0);
  EXPECT_DOUBLE_EQ(def.max().toDouble(), 10.0);
  EXPECT_DOUBLE_EQ(def.min().toDouble(), 0.0);
  def.set_tool_tip("test");
  EXPECT_TRUE(def.tool_tip() == "test");
}

TEST(PropertyDef, SubPropertyDef)
{
  // def1
  // - "test1": def0
  //    - "test1": sub_0

  smesh::PropertyDef def0(QVariant::Int);
  smesh::PropertyDef def1(QVariant::Double);

  auto sub_0 = def0.AddSubProperty("test1", QVariant::Int);
  ASSERT_TRUE(sub_0 != nullptr);

  sub_0->set_default_value(15);
  EXPECT_TRUE(sub_0->default_value().toInt() == def0.sub_property_def("test1")->default_value().toInt());
  EXPECT_TRUE(def0.sub_property_def("test1")->default_value().toInt() == 15);

  bool res_0 = def0.AddSubProperty("test1", def1);
  EXPECT_FALSE(res_0);

  def0.set_default_value(11);
  bool res_1 = def1.AddSubProperty("test1", def0);
  EXPECT_TRUE(res_1);
  def0.set_default_value(10);
  EXPECT_TRUE(def1.sub_property_def("test1")->default_value().toInt() == 11);
  EXPECT_TRUE(def0.default_value().toInt() == 10);

  EXPECT_TRUE(def1.sub_property_def("test1/test1")->default_value().toInt() == 15);
  EXPECT_TRUE(def1.sub_property_def("test1")->sub_property_def("test1")->default_value().toInt() == 15);
  EXPECT_EQ(def1.sub_property_def("test1")->sub_property_def("test1"), def1.sub_property_def("test1/test1"));
  EXPECT_TRUE(def0.sub_property_def("test1")->default_value().toInt() == 15);
}