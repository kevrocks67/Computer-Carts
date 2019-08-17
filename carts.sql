CREATE TABLE ComputerCarts (
 	CartNumber INTEGER PRIMARY KEY,
	ComputerType TEXT NOT NULL,
	Quantity INTEGER DEFAULT NULL,
	CurrentLocation VARCHAR(16) DEFAULT NULL,
	CurrentLocTime VARCHAR(16) DEFAULT NULL,
	FutureResId INTEGER DEFAULT NULL,
	CartStatus BOOLEAN DEFAULT NULL,
	OS  VARCHAR(16) NOT NULL,
	LockType VARCHAR(16) DEFAULT NULL,
	HomeLocation VARCHAR(16) DEFAULT NULL,
	LastUpdate DATETIME,
	Comments TEXT DEFAULT NULL
);
CREATE TABLE Reservations (
	ResId INTEGER NOT NULL PRIMARY KEY AUTO_INCREMENT,
	CartNumber INTEGER DEFAULT NULL,
	Location VARCHAR(16) NOT NULL,
	Date DATE NOT NULL,
	Time TIME NOT NULL,
	Comments TEXT DEFAULT NULL
);
CREATE TABLE Laptops (
	AssetID VARCHAR(32) UNIQUE DEFAULT NULL,
	Brand VARCHAR(32) NOT NULL,
	GenericName VARCHAR(32) NOT NULL,
	Model VARCHAR(32) DEFAULT NULL,
	Serial TEXT DEFAULT NULL,
	OS VARCHAR(16) NOT NULL,
	CartNumber INTEGER DEFAULT NULL,
	Status VARCHAR(16) DEFAULT NULL,
	IsDeployed BOOLEAN NOT NULL,
	FOREIGN KEY(CartNumber) REFERENCES ComputerCarts(CartNumber)
);
