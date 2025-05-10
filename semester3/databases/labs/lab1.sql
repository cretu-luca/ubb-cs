CREATE DATABASE CityPlanning;

USE CityPlanning;

IF OBJECT_ID('EmployeeProject', 'U') IS NOT NULL DROP TABLE EmployeeProject;
IF OBJECT_ID('Employee', 'U') IS NOT NULL DROP TABLE Employee;
IF OBJECT_ID('Project', 'U') IS NOT NULL DROP TABLE Project;
IF OBJECT_ID('Supplier', 'U') IS NOT NULL DROP TABLE Supplier;
IF OBJECT_ID('Sponsorship', 'U') IS NOT NULL DROP TABLE Sponsorship;
IF OBJECT_ID('Position', 'U') IS NOT NULL DROP TABLE Position;
IF OBJECT_ID('Transactions', 'U') IS NOT NULL DROP TABLE Transactions;
IF OBJECT_ID('Department', 'U') IS NOT NULL DROP TABLE Department;
IF OBJECT_ID('City', 'U') IS NOT NULL DROP TABLE City;
IF OBJECT_ID('Budget', 'U') IS NOT NULL DROP TABLE Budget;

CREATE TABLE Budget (
    BudgetID INT IDENTITY(1,1) NOT NULL PRIMARY KEY,
    TotalValue INT,
    SpentSoFar INT
);

CREATE TABLE City (
    CityID INT IDENTITY(1,1) NOT NULL PRIMARY KEY,
    CityName VARCHAR(20),
    BudgetID INT NOT NULL,
    Population INT,
    Surface INT,
    FOREIGN KEY (BudgetID) REFERENCES Budget(BudgetID) ON DELETE CASCADE
);

CREATE TABLE Department (
    DepartmentID INT IDENTITY(1,1) NOT NULL PRIMARY KEY,
    DepartmentName VARCHAR(20),
    EmployeesNumber INT,
    CityID INT NOT NULL,
    FOREIGN KEY (CityID) REFERENCES City(CityID) ON DELETE CASCADE
);

CREATE TABLE Transactions (
    TransactionID INT IDENTITY(1,1) NOT NULL PRIMARY KEY,
    Price         INT,
    Date          DATE,
    DepartmentID  INT NOT NULL,
    FOREIGN KEY (DepartmentID) REFERENCES Department(DepartmentID) ON DELETE CASCADE
);

CREATE TABLE Position (
    PositionID INT IDENTITY(1,1) NOT NULL PRIMARY KEY,
    PositionName VARCHAR(20),
    Salary INT,
    EducationLevel VARCHAR(20)
);

CREATE TABLE Supplier (
    SupplierID INT IDENTITY(1,1) NOT NULL PRIMARY KEY,
    SupplierName VARCHAR(20),
    Revenue INT,
    FoundingDate DATE
);

CREATE TABLE Sponsorship (
    SponsorshipID INT IDENTITY(1,1) NOT NULL PRIMARY KEY,
    SponsorName VARCHAR(20),
    Value INT
);

CREATE TABLE Project (
    ProjectID INT IDENTITY(1,1) NOT NULL PRIMARY KEY,
    ProjectName VARCHAR(20),
    StartDate DATE,
    EndDate DATE,
    SupplierID INT NOT NULL,
    SponsorshipID INT NOT NULL,
    FOREIGN KEY (SupplierID) REFERENCES Supplier(SupplierID) ON DELETE CASCADE,
    FOREIGN KEY (SponsorshipID) REFERENCES Sponsorship(SponsorshipID) ON DELETE CASCADE
);

CREATE TABLE Employee (
    EmployeeID INT IDENTITY(1,1) NOT NULL PRIMARY KEY,
    Name VARCHAR(20),
    DepartmentID INT NOT NULL,
    PositionID INT NOT NULL,
    FOREIGN KEY (DepartmentID) REFERENCES Department(DepartmentID) ON DELETE CASCADE,
    FOREIGN KEY (PositionID) REFERENCES Position(PositionID) ON DELETE CASCADE
);

CREATE TABLE EmployeeProject (
    EmployeeID INT,
    ProjectID INT,
    PRIMARY KEY (EmployeeID, ProjectID),
    FOREIGN KEY (EmployeeID) REFERENCES Employee(EmployeeID),
    FOREIGN KEY (ProjectID) REFERENCES Project(ProjectID)
);
