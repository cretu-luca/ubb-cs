DROP TABLE Employee
DROP TABLE Position
DROP TABLE Transactions
DROP TABLE Department
DROP TABLE City
DROP TABLE Budget

DROP TABLE Project
DROP TABLE Supplier
DROP TABLE Sponsorship
DROP TABLE EmployeeProject

CREATE TABLE Budget (
    BudgetID INT NOT NULL PRIMARY KEY,
    TotalValue INT,
    SpentSoFar INT
)

CREATE TABLE City (
    CityID INT NOT NULL PRIMARY KEY,
    CityName VARCHAR(20),
    BudgetID INT,
    Population INT,
    Surface INT,
    FOREIGN KEY (BudgetID) REFERENCES Budget(BudgetID) ON DELETE CASCADE
)

CREATE TABLE Department (
    DepartmentID INT NOT NULL PRIMARY KEY,
    DepartmentName VARCHAR(20),
    EmployeesNumber INT,
    CityID INT,
    FOREIGN KEY (CityID) REFERENCES City(CityID) ON DELETE CASCADE
)

CREATE TABLE Transactions (
    TransactionID INT NOT NULL PRIMARY KEY,
    Price         INT,
    Date          DATE,
    DepartmentID  INT,
    FOREIGN KEY (DepartmentID) REFERENCES Department (DepartmentID) ON DELETE CASCADE
)

CREATE TABLE Position (
    PositionID INT NOT NULL PRIMARY KEY,
    ProjectName VARCHAR(20),
    Salary INT,
    EducationLevel VARCHAR(20)
)

CREATE TABLE Supplier (
    SupplierID INT NOT NULL PRIMARY KEY,
    SupplierName VARCHAR(20),
    Revenue INT,
    FoundingDate DATE,
    ProjectID INT
)

CREATE TABLE Sponsorship (
    SponsorshipID INT NOT NULL PRIMARY KEY,
    SponsorName VARCHAR(20),
    Value INT
)

CREATE TABLE Project (
                         ProjectID INT NOT NULL PRIMARY KEY,
                         ProjectName VARCHAR(20),
                         StartDate DATE,
                         EndDate DATE,
                         SupplierID INT,
                         SponsorshipID INT,
                         FOREIGN KEY (SupplierID) REFERENCES Supplier(SupplierID) ON DELETE CASCADE,
                         FOREIGN KEY (SponsorshipID) REFERENCES Sponsorship(SponsorshipID) ON DELETE CASCADE
)

CREATE TABLE Employee (
    EmployeeID INT NOT NULL PRIMARY KEY,
    Name VARCHAR(20),
    DepartmentID INT,
    PositionID INT,
    FOREIGN KEY (DepartmentID) REFERENCES Department(DepartmentID) ON DELETE CASCADE,
    FOREIGN KEY (PositionID) REFERENCES Position(PositionID) ON DELETE CASCADE
)

CREATE TABLE EmployeeProject (
    EmployeeID INT,
    ProjectID INT,
    PRIMARY KEY (EmployeeID, ProjectID),
    FOREIGN KEY (EmployeeID) REFERENCES Employee(EmployeeID),
    FOREIGN KEY (ProjectID) REFERENCES Project(ProjectID)
)