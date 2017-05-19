#include <iostream>
#include <fstream>
#include <set>
#include <sstream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include "product.h"
#include "mydatastore.h"
#include "db_parser.h"
#include "product_parser.h"
#include "util.h"
#include "mainwindow.h"
#include <QApplication>




using namespace std;

int main(int argc, char* argv[])
{
    if(argc < 2) {
        cerr << "Please specify a database file" << endl;
        return 1;
    }

    /****************
     * You may modify this allocation and type if you need
     ****************/
    MyDataStore* ds = new MyDataStore;



    // Instantiate the individual section and product parsers we want
    ProductSectionParser* productSectionParser = new ProductSectionParser;
    productSectionParser->addProductParser(new ProductBookParser);
    productSectionParser->addProductParser(new ProductClothingParser);
    productSectionParser->addProductParser(new ProductMovieParser);
    UserSectionParser* userSectionParser = new UserSectionParser;
    ReviewSectionParser* reviewSectionParser = new ReviewSectionParser;

    // Instantiate the parser
    DBParser parser;
    parser.addSectionParser("products", productSectionParser);
    parser.addSectionParser("users", userSectionParser);
    parser.addSectionParser("reviews", reviewSectionParser);

    // Now parse the database to populate the DataStore
    if( parser.parse(argv[1], *ds) ) {
        cerr << "Error parsing!" << endl;
        return 1;
    }

    QApplication app(argc, argv);

    MainWindow mainWindow(ds);
    mainWindow.show();

    return app.exec();
}

