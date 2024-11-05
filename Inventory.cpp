/**********************
*
* File Name:    Inventory.cpp
* Author(s):
* Description:
*
* Course:      CSC 455 - Software Quality Assurance
* Instructor:  Mohammed Belkhouche
* Project:     Term Project
* Date:        8 November 2024
*
***********************/

#include "Includes.cpp"

class Inventory:public map<int, Product::Product>{
    private:


    public:
      //Product Addition
      int createProduct(Product::Product);

      //Product Removal
      int deleteProduct(int ProductID);

      //Shopping
      Product::Product getProduct(int ProductID);

}