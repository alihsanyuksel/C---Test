#include "gtest/gtest.h" // Include Google Test
#include "productManager.cpp" // Include your header file (where the above code is)

TEST(ProductTest, ProductCreation) {
    Product p(1, "Test Product", 99.99);
    ASSERT_EQ(p.id, 1);
    ASSERT_EQ(p.name, "Test Product");
    ASSERT_DOUBLE_EQ(p.price, 99.99);
}

TEST(ProductManagerTest, AddAndFindProduct) {
    ProductManager manager;
    Product p1(1, "Product 1", 10.0);
    manager.addProduct(p1);

    Product* found = manager.findProduct(1);
    ASSERT_NE(found, nullptr);
    ASSERT_EQ(found->name, "Product 1");
}

TEST(ProductManagerTest, FindNonExistentProduct) {
    ProductManager manager;
    Product* found = manager.findProduct(99); // Non-existent ID
    ASSERT_EQ(found, nullptr);
}

TEST(ProductManagerTest, RemoveProduct) {
    ProductManager manager;
    Product p1(1, "Product 1", 10.0);
    manager.addProduct(p1);

    ASSERT_TRUE(manager.removeProduct(1));
    ASSERT_EQ(manager.findProduct(1), nullptr); // Check if really removed
    ASSERT_FALSE(manager.removeProduct(1)); //Try to remove again, should fail.
}

TEST(ProductManagerTest, GetAllProducts) {
    ProductManager manager;
    Product p1(1, "Product 1", 10.0);
    Product p2(2, "Product 2", 20.0);
    manager.addProduct(p1);
    manager.addProduct(p2);

    const std::vector<Product>& allProducts = manager.getAllProducts();
    ASSERT_EQ(allProducts.size(), 2);
    ASSERT_EQ(allProducts[0].name, "Product 1");
    ASSERT_EQ(allProducts[1].price, 20.0);
}

TEST(ProductManagerTest, GetTotalPrice){
    ProductManager manager;
    Product p1(1, "Product 1", 10.0);
    Product p2(2, "Product 2", 20.0);
    Product p3(3, "Product 3", 30.0);

    manager.addProduct(p1);
    manager.addProduct(p2);
    manager.addProduct(p3);

    ASSERT_DOUBLE_EQ(manager.getTotalPrice(), 60.0);
    ProductManager emptyManager;
    ASSERT_DOUBLE_EQ(emptyManager.getTotalPrice(), 0.0);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}