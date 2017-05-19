#include "mainwindow.h"

using namespace std;

MainWindow::MainWindow(MyDataStore* ds)
{
	this->ds = ds;

	int x=width()*1.2; 
    int y=height()*1.5;

    setFixedSize(x,y);

	overallLayout = new QVBoxLayout(); //main window

	outerVLayout = new QGridLayout();
	overallLayout->addLayout(outerVLayout);
	overallLayout->addLayout(outerVLayout);

	loginLayout = new QGridLayout(); //loginWindow

	initialLayout = new QHBoxLayout();
	mainWindow = new QWidget();
	loginWindow = new QWidget();
	initialLayout->addWidget(mainWindow);
	initialLayout->addWidget(loginWindow);

	mainWindow->hide();
	
	mainWindow->setLayout(overallLayout);


	loginWindow->setLayout(loginLayout);

	innerHLayout1 = new QHBoxLayout();
	innerHLayout2 = new QHBoxLayout();
	innerHLayout3 = new QHBoxLayout();
	innerVLayout4 = new QVBoxLayout();
	innerHLayout5 = new QHBoxLayout();
	innerHLayout6 = new QHBoxLayout();
	innerHLayout7 = new QHBoxLayout();
	innerHLayout8 = new QHBoxLayout(); //logInSection
	innerHLayout9 = new QHBoxLayout(); //3 login buttons

	sortDropDown = new QComboBox();

	vector<User*> allUsers = ds->userList;
	QPixmap pixmap = QPixmap (":/user.png");
	string sortAlpha = "Sort by product name";
	string sortRating = "Sort by highest rating";

	sortDropDown->addItem(QString::fromStdString(sortAlpha));
	sortDropDown->addItem(QString::fromStdString(sortRating));




	addButton = new QPushButton();

	//outerVLayout->addLayout(searchResults, 2, 0);
	
	//SEARCH UI
	//searchBox = new QGroupBox("Search");
	
	searchButton = new QPushButton("Search!");
	andSearchButton = new QRadioButton("AND");
	orSearchButton = new QRadioButton("OR");
	searchField = new QLineEdit();
	dataBaseNameField = new QLineEdit();

	searchField->setPlaceholderText("Search for a product"); //sets grey text in textbox
	dataBaseNameField->setPlaceholderText("Enter save filename here before saving"); //sets grey text in textbox
	addButton = new QPushButton("Add to cart");
	addReviewButton = new QPushButton("Add review");
	buyCartButton = new QPushButton("Checkout");
	saveButton = new QPushButton("Save database");
	quitButton = new QPushButton("Quit");
	recommendedProductsButton = new QPushButton("Product Recommendations");
	removeItemFromCartButton = new QPushButton("Remove Item");
	quoteListWidget = new QListWidget();
	quoteListWidget2 = new QListWidget();
	selectedProductDescription = new QListWidget();
	selectedProductReviews = new QListWidget();
	cartItemsBox = new QListWidget();

	usernameField = new QLineEdit();
	passwordField = new QLineEdit();
	usernameField->setPlaceholderText("Username");
	passwordField->setPlaceholderText("Password");

	loginButton = new QPushButton("Log In");
	newUserButton = new QPushButton("Sign up");
	quitButton2 = new QPushButton("Quit");
	innerHLayout8->addWidget(usernameField);
	innerHLayout8->addWidget(passwordField);

	innerHLayout9->addWidget(loginButton);
	innerHLayout9->addWidget(newUserButton);
	innerHLayout9->addWidget(quitButton2);


	loginLayout->addLayout(innerHLayout8, 0 ,0 );
	loginLayout->addLayout(innerHLayout9, 1 ,0 );

	outerVLayout->addLayout(innerHLayout1, 0, 0);
	outerVLayout->addLayout(innerHLayout2, 1, 0);
	outerVLayout->addWidget(sortDropDown, 2, 0);
	outerVLayout->addLayout(innerHLayout3, 3, 0);
	outerVLayout->addWidget(addReviewButton, 4, 0);
	outerVLayout->addWidget(recommendedProductsButton, 5, 0);
	outerVLayout->addLayout(innerHLayout5, 6, 0);
	outerVLayout->addWidget(cartItemsBox, 7, 0);
	outerVLayout->addLayout(innerHLayout6, 8, 0);
	outerVLayout->addLayout(innerHLayout7, 9, 0);
	outerVLayout->addWidget(quitButton, 10, 0);
	outerVLayout->addWidget(quoteListWidget2, 11, 0);
	innerHLayout3->setSpacing(0);	
	innerHLayout3->setMargin(0);
	innerHLayout2->setContentsMargins(0,0,0,0);
	innerHLayout3->setContentsMargins(0,0,0,0);
	innerHLayout5->setContentsMargins(0,0,0,10);
	innerHLayout6->setContentsMargins(0,0,0,0);
	innerHLayout1->addWidget(searchField); //adds search input to top row
	innerHLayout1->addWidget(searchButton); //adds "Search!" button to top row
	innerHLayout2->addWidget(andSearchButton); //adds radio button to bottom row
	innerHLayout2->addWidget(orSearchButton);	//adds radio button to bottom row
	innerHLayout3->addWidget(quoteListWidget); 
	innerHLayout3->addLayout(innerVLayout4);
	innerVLayout4->addWidget(selectedProductDescription);
	innerVLayout4->addWidget(selectedProductReviews);
	innerHLayout5->addWidget(addButton);
	innerHLayout6->addWidget(removeItemFromCartButton);
	innerHLayout6->addWidget(buyCartButton);
	innerHLayout7->addWidget(dataBaseNameField);
	innerHLayout7->addWidget(saveButton);

	QObject::connect(searchButton, SIGNAL( clicked() ), this, SLOT(searchProducts() ) );
	QObject::connect(addButton, SIGNAL( clicked() ), this, SLOT(addToCart() ) );
	QObject::connect(sortDropDown, SIGNAL(  currentIndexChanged(int) ), this, SLOT(sortSearch() ) );

	QObject::connect(addButton, SIGNAL( clicked() ), this, SLOT(cartWindow() ) );
	QObject::connect(quoteListWidget, SIGNAL( itemSelectionChanged() ), this, SLOT(productInfo() ) );
	QObject::connect(removeItemFromCartButton, SIGNAL( clicked() ), this, SLOT(deleteCartItem() ) );
	QObject::connect(buyCartButton, SIGNAL( clicked() ), this, SLOT(buyCart() ) );
	QObject::connect(saveButton, SIGNAL( clicked() ), this, SLOT(savetoDatabase() ) );
	QObject::connect(quitButton, SIGNAL( clicked() ), this, SLOT(quitClicked() ) );
	QObject::connect(quitButton2, SIGNAL( clicked() ), this, SLOT(quitClicked() ) );
	QObject::connect(addReviewButton, SIGNAL( clicked() ), this, SLOT(addReview() ) );
	QObject::connect(loginButton, SIGNAL( clicked() ), this, SLOT(login() ) );
	QObject::connect(newUserButton, SIGNAL( clicked() ), this, SLOT(addUser() ) );
	QObject::connect(recommendedProductsButton, SIGNAL( clicked() ), this, SLOT(makeRecommendation() ) );


	setLayout(initialLayout);
}

void MainWindow::searchProducts()
{
	// Do nothing if user left at least one input blank
	if(searchField->text().isEmpty())
	{
		return;
	}

	if( andSearchButton->isChecked()) 
	{

		string userInput = searchField->text().toStdString();
		istringstream ss(userInput);
        string term;
        vector<string> terms;
        while(ss >> term) 
        {
            term = convToLower(term);
            terms.push_back(term);
        }
        hits = ds->search(terms, 0);
        displayProducts(hits);
	}
	else if ( orSearchButton->isChecked() ) 
	{	

		string userInput = searchField->text().toStdString();
		istringstream ss(userInput);
        string term;
        vector<string> terms;
        while(ss >> term) 
        {
            term = convToLower(term);
            terms.push_back(term);
        }
        hits = ds->search(terms, 1);
        displayProducts(hits);
    }
	// Get form values
    string userInput = searchField->text().toStdString();
    cout << userInput << endl;

// 	quotes.push_back(quoteInput->toPlainText().toStdString());


// 	// Create a new list item with the person's name
//     quoteListWidget->addItem(personInput->text());


// 	// Clear the form inputs
// 	personInput->setText("");
}

void MainWindow::displayProducts(vector<Product*>& hits)
{
	quoteListWidget->clear();
    int resultNo = 1;
    for(vector<Product*>::iterator it = hits.begin(); it != hits.end(); ++it) {
        cout << "Hit " << setw(3) << resultNo << endl;
        cout << (*it)->displayString() << endl;
        cout << endl;

        string output = (*it)->getName();
        QString qstr = QString::fromStdString(output);
		quoteListWidget->addItem(qstr);
        resultNo++;
    }

}


void MainWindow::makeRecommendation()
{
	quoteListWidget2->clear();
	int resultNo = 1;
	vector<pair<string, double> > recommendations = ds->makeSuggestion();
	//sort the vector of pairs by their second value here.
	// vector<std::pair<string, double> > input;
	// recommendations.push_back(make_pair("Alex", 1.0)); 
	// recommendations.push_back(make_pair("Sahsa", 3.0)); 
	// recommendations.push_back(make_pair("Masha", 2.0)); 
	// recommendations.push_back(make_pair("elenaa", 4.0));
	string filename = "rec.txt";
	ofstream ofile(filename.c_str());
	ofile << ds->loggedInUser->getName() << endl;
	cout << "recs size = " << recommendations.size() << endl;
	mergeSort(recommendations, prodRecommend());
	for(int i = 0; i < (int)recommendations.size(); i++) 
	{
		std::ostringstream strs;
		strs << "Recommendation " << setw(3) << resultNo << endl;
		cout << "Recommendation " << setw(3) << resultNo << endl;
		// Product* a = findProductByName(it->first);
		// if (a != NULL)
		// {
		if(recommendations.at(i).second != 0)
		{
		strs << recommendations.at(i).first << '\n' << "Score: " << recommendations.at(i).second;
		cout << recommendations.at(i).first << '\n' << "Score: " << recommendations.at(i).second << endl;
		
    	ofile << recommendations.at(i).second << ' ' << recommendations.at(i).first << endl;

    	
		// }
		// strs << (*it).first << '\n' << "Score: " << (*it).second;

		std::string str = strs.str();
		QString qstr = QString::fromStdString(str);
		quoteListWidget2->addItem(qstr);
		}
		resultNo++;
	}
	ofile.close();
}



void MainWindow::addReview()
{


	int yearInt;
	int monthInt;
	int dayInt;
	int ratingInt;

	string year;
	string month;
	string day;
	string rating;
	string reviewText;
	User* username;
	Product* selectedProduct;
	selectedProduct = this->selectedProduct();

	string date;
	Review* review;




	QMessageBox msgBox;

	msgBox.setText("Please enter your review!");
	QLineEdit monthLine;
	QLineEdit dayLine;
	QLineEdit yearLine;
	monthLine.setPlaceholderText("Month (1-12)");
	dayLine.setPlaceholderText("Day (1-31)");
	yearLine.setPlaceholderText("Year (2016-2030)");

	QLineEdit ratingLine;
	ratingLine.setPlaceholderText("Rating (1-5)");

	QLineEdit reviewTextLine;
	reviewTextLine.setPlaceholderText("Review");

	msgBox.layout()->addWidget(&ratingLine);
	msgBox.layout()->addWidget(&reviewTextLine);
	msgBox.layout()->addWidget(&monthLine);
	msgBox.layout()->addWidget(&dayLine);
	msgBox.layout()->addWidget(&yearLine);






	msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Cancel);
	msgBox.setDefaultButton(QMessageBox::Save);
	int ret = msgBox.exec();




	switch (ret) {
	case QMessageBox::Save:

		year = yearLine.text().toStdString();
		month = monthLine.text().toStdString();
		day = dayLine.text().toStdString();
		rating = ratingLine.text().toStdString();
		reviewText = reviewTextLine.text().toStdString();
		username = ds->loggedInUser;

		if(username != NULL  && selectedProduct != NULL && year.length() != 0 && month.length() != 0 && day.length() != 0 && rating.length() != 0 && reviewText.length() != 0 )
		{
			cout << "got here" << endl;
			stringstream yearss(year);
			yearss >> yearInt;
			stringstream monthss(month);
			monthss >> monthInt;
			stringstream dayss(day);
			dayss >> dayInt;
			stringstream ratingss(rating);
			ratingss >> ratingInt;
			if(yearInt > 2015 && yearInt < 2031 && monthInt > 0 && monthInt < 13 && dayInt > 0 && dayInt < 32 && ratingInt > 0 && ratingInt < 6)
			{
				if(monthInt < 10)
				{
					month = '0' + month;
				}
				if(dayInt < 10)
				{
					day = '0' + day;
				}
				date = year + '-' + month + '-' + day;
				review = new Review(selectedProduct->getName(),
		           ratingInt,
		           username->getName(),
		           date,
		           reviewText);

				ds->addReview(review);

			}

		}
		break;
	case QMessageBox::Cancel:
		break;
	default:
		break;
 }
 productInfo();
}


void MainWindow::addToCart()
{
	User* username = ds->loggedInUser;
	if(username != NULL) //found user by username
    {
    	if(selectedProduct() != NULL)
    	{
        	username->addToCart(selectedProduct());

        	cout << "Added " << selectedProduct()->getName() << " to " << username->getName() << "'s cart." << endl;
    	}
    }  
    else
    {
        cout << "Invalid request" << endl;
    }



	// QListIterator<QListWidgetItem*> i(listOfSelectedItems);
	// while (i.hasNext())
	// {
 	//    	string selectedItem = (&i).text().toStdString();
 	//    	cout << selectedItem << endl;
	// }

}


void MainWindow::cartWindow()
{

	User* username = ds->loggedInUser;
	if(username != NULL) //found user by username
    {
    	cartItemsBox->clear();
    	std::ostringstream strs;
		strs << username->getBalance();
		std::string userBalance = strs.str();

    	string titlestring = username->getName() + "'S CART" + " | $" + userBalance;
    	for (std::string::size_type i=0; i<titlestring.length(); ++i)
   		titlestring[i] = std::toupper(titlestring[i]);

    	QString title = QString::fromStdString(titlestring);
    	cartItemsBox->addItem(title);

    	ofstream os;

    	std::deque<Product *> selectedUserscart = username->cart;

        string output;

		for(deque<Product*>::iterator it = selectedUserscart.begin(); it != selectedUserscart.end(); ++it) 
		{
			output = (*it)->getName();
			QString qstr = QString::fromStdString(output);
			cartItemsBox->addItem(qstr);
		}



    }  
}

void MainWindow::deleteCartItem()
{
	Product* selectedProduct = selectedCartProduct();
	User* username = ds->loggedInUser;
	if(selectedProduct == NULL)
	{
		return;
	}
	username->deleteCartItem(selectedProduct);
	cartWindow();
	
}
void MainWindow::buyCart()
{
	User* username = ds->loggedInUser;
    if(username != NULL) //found user by username
    {
        username->buyCart();
        cartWindow();
        productInfo();
    }  
    else
    {
        cout << "Invalid request" << endl;
    }
}

void MainWindow::productInfo()
{
	Product* currentSelectedProduct = selectedProduct();
	if(selectedProduct() != NULL)
	{
		//Product Description
		selectedProductDescription->clear();
		selectedProductReviews->clear();

		string description = selectedProduct()->displayString();

		QString qstr = QString::fromStdString(description);
		selectedProductDescription->addItem(qstr);

		//Product Reviews 
		string fullReviewString;
		mergeSort(currentSelectedProduct->reviewList, reviewDate());
		for(int i=0; i < (int)(currentSelectedProduct->reviewList.size()); i++)
		{
			std::ostringstream strs;
			strs << currentSelectedProduct->reviewList.at(i)->rating;
			std::string rating = strs.str();
			fullReviewString = currentSelectedProduct->reviewList.at(i)->username + " | " + currentSelectedProduct->reviewList.at(i)->date + 
			'\n' + rating + "/5 | " + '\"' + currentSelectedProduct->reviewList.at(i)->reviewText + '\"';

			QString qstr2 = QString::fromStdString(fullReviewString);
			selectedProductReviews->addItem(qstr2);
		}
	}
}

void MainWindow::sortSearch()
{
	string sortBy = (sortDropDown->currentText() ).toStdString();
	cout << sortBy << endl;
	if (sortBy == "Sort by highest rating")
	{
		cout << "rating" << endl;
		mergeSort(hits, averageRating());
		cout << "rating" << endl;
		displayProducts(hits);
	}
	if (sortBy == "Sort by product name")
	{
		mergeSort(hits, productName());
		displayProducts(hits);
	}

}
void MainWindow::login()
{
	string username = usernameField->text().toStdString();
	string password = passwordField->text().toStdString();
	unsigned int hashNum = hashFunction(password);

	User* user = findUserByName(username);
	if(user != NULL)
	{
		if(hashNum == user->getHashNum())
		{
			//LOG IN.
			ds->loggedInUser = user;
			usernameField->clear();
			passwordField->clear();
			loginWindow->hide();
			mainWindow->show();
			cartWindow();
		}
		else
		{
			usernameField->clear();
			passwordField->clear();
			QMessageBox mymsg(this);  // this is the pointer to the current widget
      		mymsg.setText("Incorrect password. Try again.");
      		mymsg.exec();
			cout << "Incorrect password. Try again." << endl;
			cout << user->getHashNum() << endl;
		}
	}
	else
	{
		QMessageBox mymsg(this);  // this is the pointer to the current widget
      	mymsg.setText("Username does not exist");
      	mymsg.exec();
		cout << "Username " << username << " does not exist" << endl;
		usernameField->clear();
		passwordField->clear();
	}
}


void MainWindow::addUser()
{
	string username = usernameField->text().toStdString();
	string password = passwordField->text().toStdString();
	if(password.size() > 8)
	{
		QMessageBox mymsg(this);  // this is the pointer to the current widget
      	mymsg.setText("Password longer than 8 characters.");
      	mymsg.exec();
		return;
	}
	else
	{
		unsigned int hashNum = hashFunction(password);

		User* user = findUserByName(username);
		if(user == NULL) //no user with inputted username exists
		{
			User* user = new User(username, 100.0, 0, hashNum);
			ds->addUser(user);
			cout << "Added user " << user->getName() << endl;
			usernameField->clear();
			passwordField->clear();
		}
	}
}


unsigned int MainWindow::hashFunction(string input)
{
	unsigned int returnHash = 0;
	unsigned long long temp = 0;
	unsigned long long size = input.length();
	for(unsigned long long i = 0; i < size; i++)
	{
		unsigned long long oneChar = (unsigned long long)input[i];
		temp+= oneChar * (unsigned long long)pow(128, size - i - 1);

	}
	unsigned int w4 = temp%65521;
    unsigned int w3 = (temp/65521)%65521;
    unsigned int w2 = ((temp/65521)/65521)%65521;
    unsigned int w1 = (((temp/65521)/65521)/65521)%65521;
    returnHash = (45912 * w1 + 35511 * w2 + 65169 * w3 + 4625 * w4) % 65521;




	return returnHash;
}

Product* MainWindow::findProductByName(string findName)
{
	Product* returnProduct = NULL;
	vector<Product*> allProducts = ds->productList;
	for(int i =0; i<(int)allProducts.size(); i++)
	{
		if(findName == allProducts.at(i)->getName())
		{
			returnProduct = allProducts.at(i);
		}
	}
	return returnProduct;
}

User* MainWindow::findUserByName(string findName)
{
	User* returnUser = NULL;
	vector<User*> allUsers = ds->userList;
	for(int i =0; i<(int)allUsers.size(); i++)
	{
		if(findName == allUsers.at(i)->getName())
		{
			returnUser = allUsers.at(i);
		}
	}
	return returnUser;
}

Product* MainWindow::selectedProduct()
{
	Product* returnProduct = NULL;

	QList<QListWidgetItem*> listOfSelectedItems;
	listOfSelectedItems = quoteListWidget->selectedItems();
	if(listOfSelectedItems.size() == 0)
	{
		return returnProduct;
	}
	string selectedItem = (listOfSelectedItems.first()->text()).toStdString();
	returnProduct = findProductByName(selectedItem);
	return returnProduct;
}

Product* MainWindow::selectedCartProduct()
{
	Product* returnProduct = NULL;

	QList<QListWidgetItem*> listOfSelectedItems;
	listOfSelectedItems = cartItemsBox->selectedItems();
	if(listOfSelectedItems.size() == 0)
	{
		return returnProduct;
	}
	string selectedItem = (listOfSelectedItems.first()->text()).toStdString();
	returnProduct = findProductByName(selectedItem);
	return returnProduct;
}
void MainWindow::savetoDatabase()
{	
	if(dataBaseNameField->text().isEmpty())
	{
		return;
	}
    string filename = dataBaseNameField->text().toStdString();
    ofstream ofile(filename.c_str());
    ds->dump(ofile);
    ofile.close();
}
void MainWindow::quitClicked()
{
	close();
}
MainWindow::~MainWindow()
{
	// delete overallLayout;
	// delete outerVLayout;
	delete innerHLayout1;
	delete innerHLayout2;
	// delete innerHLayout3;
	delete innerVLayout4;
	delete innerHLayout5;
	delete innerHLayout6;
	delete innerHLayout7;

	delete sortDropDown;


	//QGroupBox* searchBox;
	delete searchButton;
	delete searchField;
	delete dataBaseNameField;

	delete andSearchButton;
	delete orSearchButton;
	delete ds;
	delete quoteListWidget;
	delete selectedProductDescription;
	delete selectedProductReviews;
	delete addButton;
	delete cartItemsBox;
	delete buyCartButton;
	delete addReviewButton;
	delete removeItemFromCartButton;
	delete saveButton;
	delete quitButton;

}


