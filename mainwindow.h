#include <iostream>
#include <fstream>
#include <set>
#include <sstream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <QObject>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QRadioButton>
#include <QComboBox>
#include <QMessageBox>
#include <QString>
#include <QListWidget>
#include <QIcon>
#include <QPixmap>
#include <QListIterator>
#include <string>
#include <locale> 

#include "msort.h"
#include "product.h"
#include "db_parser.h"
#include "product_parser.h"
#include "util.h"
#include "mydatastore.h"

#include <fstream>
#include <cmath>
using namespace std;

class MainWindow : public QWidget
{
	Q_OBJECT
public:
	MainWindow(MyDataStore* ds);
	~MainWindow();
	void displayProducts(vector<Product*>&);
	Product* selectedProduct();
	Product* selectedCartProduct();
	Product* findProductByName(string);
	User* findUserByName(string);
	User* loggedInUser;
	struct ProdNameSorter {
    bool operator()(Product* p1, Product* p2) {
        return (p1->getName() < p2->getName());
    };
};


private slots:
	void searchProducts();
	void addToCart();
	void cartWindow();
	void productInfo();
	void deleteCartItem();
	void buyCart();
	void quitClicked();
	void savetoDatabase();
	void sortSearch();
	void addReview();
	void login();
	void addUser();
	void makeRecommendation();
private:
	vector<Product*> hits;
	QVBoxLayout* overallLayout;
	QHBoxLayout* initialLayout;
	QGridLayout* loginLayout;

	QWidget* mainWindow; 
	QWidget* loginWindow; 
	QGridLayout* outerVLayout;
	QHBoxLayout* innerHLayout1;
	QHBoxLayout* innerHLayout2;
	QHBoxLayout* innerHLayout3;
	QVBoxLayout* innerVLayout4;
	QHBoxLayout* innerHLayout5;
	QHBoxLayout* innerHLayout6;
	QHBoxLayout* innerHLayout7;
	QHBoxLayout* innerHLayout8;
	QHBoxLayout* innerHLayout9;


	QComboBox* sortDropDown;

	unsigned int hashFunction(string pw);
	//QGroupBox* searchBox;
	QPushButton* searchButton;
	QLineEdit* searchField;
	QLineEdit* dataBaseNameField;
	QLineEdit* usernameField;
	QLineEdit* passwordField;
	QRadioButton* andSearchButton;
	QRadioButton* orSearchButton;
	MyDataStore* ds;
	QListWidget* quoteListWidget;
	QListWidget* quoteListWidget2;
	QListWidget* selectedProductDescription;
	QListWidget* selectedProductReviews;
	QPushButton* addButton;
	QListWidget* cartItemsBox;
	QPushButton* buyCartButton;
	QPushButton* addReviewButton;
	QPushButton* removeItemFromCartButton;
	QPushButton* saveButton;
	QPushButton* quitButton;
	QPushButton* loginButton;
	QPushButton* quitButton2;
	QPushButton* newUserButton;
	QPushButton* recommendedProductsButton;



	// // Displayed quote
	// QGroupBox* searchBox;
	// QLineEdit* personInput;
	
	// QLabel* quoteDisplay;
	// QLabel* personDisplay;


	// // List of quotes
	// QListWidget* quoteListWidget;

	// // Form for new quote
	// QVBoxLayout* formLayout;
	// QLabel* personLabel;
	
	// QLabel* quoteLabel;
	// QTextEdit* quoteInput;
	// QPushButton* addButton;
};