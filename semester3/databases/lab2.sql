
-- Insert

INSERT INTO Budget VALUES (1, 100, 75),
                          (2, 200, 190),
                          (3, 75, 75),
                          (4, 125, 60),
                          (5, 140, 90)

INSERT INTO Budget VALUES (6, 200, 200),
                          (7, 150, 300)

-- does not work (duplicating primary key)
INSERT INTO Budget VALUES (1, 120, 100)

INSERT INTO City VALUES (1, 'Cluj', 2, 700000, 10000),
                        (2, 'Bucuresti', 4, 2000000, 20000),
                        (3, 'Bistrita', 1, 100000, 30000),
                        (4, 'Brasov', 3, 320000, 190000),
                        (5, 'Oradea', 5, 200000, 10000)


INSERT INTO City Values (6, 'Galati', 1, 100000, 250000)
INSERT INTO City Values (7, 'Ialomita', 2, 50000, 200000)

-- does not work (invalid BudgetID)
INSERT INTO CITY VALUES (6, 'Timisoara', 6, 200000, 100000)

INSERT INTO Department VALUES (1, 'Agricultura', 100, 1),
                              (2, 'Sanatate', 75, 3),
                              (3, 'Urbanizare', 120, 4),
                              (4, 'Salubrizare', 60, 2),
                              (5, 'Autorizatii public', 50, 3)

INSERT INTO Department VALUES (6, 'Fonduri Europene', 20, 4)
INSERT INTO Department VALUES (7, 'Spatii verzi', 10, 5)

-- does not work (invalid CityID)
INSERT INTO Department VALUES (6, 'Finante', 100, 6)

INSERT INTO Transactions VALUES (1, 20000, '2024-10-20', 2),
                                (2, 30000, '2023-4-12', 3),
                                (3, 10000, '2022-6-2', 1),
                                (4, 40000, '2024-2-28', 3),
                                (5, 15000, '2023-1-10', 1)

INSERT INTO Transactions VALUES (6, 20000, '2025-10-10', 5)

INSERT INTO Position VALUES (1, 'Contabil', 9000, 'Licenta'),
                            (2, 'Manager proiect', 18000, 'Master'),
                            (3, 'Programator', 200000, 'Master'),
                            (4, 'Marketing Expert', 12000, 'PhD'),
                            (5, 'Admin IT', 14000, 'Licenta')

INSERT INTO Position VALUES (6, 'Economist', 10000, 'Licenta'),
                            (7, 'Director cultural', 20000, 'PhD')

INSERT INTO Supplier VALUES (1, 'Supplier 1', 200000, '2023-5-4'),
                            (2, 'Supplier 2', 100000, '2024-5-20'),
                            (3, 'Supplier 3', 50000, '2024-3-10'),
                            (4, 'Supplier 4', 125000, '2022-12-1'),
                            (5, 'Supplier 5', 70000, '2021-5-5')

INSERT INTO Supplier VALUES (6, 'Supplier 7', 1000000, '2024-12-31')

INSERT INTO Sponsorship VALUES (1, 'BRD', 100000),
                               (2, 'BCR', 40000),
                               (3, 'ASG', 200000),
                               (4, 'FMI', 750000),
                               (5, 'BLS', 120000)

INSERT INTO Sponsorship VALUES (6, 'BDS', 10000)
INSERT INTO Sponsorship VALUES (7, 'TYS', 1000000)

INSERT INTO Project VALUES (1, 'Healthcare', '2022-5-4', '2023-5-5', 1, 2),
                           (2, 'Urbanism', '2021-5-5', '2024-2-1', 2, 3),
                           (3, 'Digitalization', '2020-1-1', '2024-1-1', 3, 1),
                           (4, 'Administration', '2023-10-20', '2024-12-12', 4, 1),
                           (5, 'Funding', '2024-10-20', '2025-1-1', 2, 4)

INSERT INTO Employee VALUES (1, 'Cretu Luca', 2, 3),
                            (2, 'Cretu Cristian', 4, 1),
                            (3, 'Greholea Denis', 1, 2),
                            (4, 'Foica Serban', 2, 4),
                            (5, 'David Liviu', 5, 1)

INSERT INTO EmployeeProject VALUES (1, 2),
                                   (2, 3),
                                   (1, 5),
                                   (4, 2),
                                   (5, 1)

-- UPDATE

UPDATE Budget
SET TotalValue = TotalValue * 2
WHERE SpentSoFar = TotalValue

UPDATE Budget
SET TotalValue = TotalValue + 10000
WHERE SpentSoFar < 100

UPDATE Department
SET DepartmentName = 'Permacultura'
WHERE DepartmentID = 1

UPDATE Department
SET EmployeesNumber = EmployeesNumber + 20
WHERE EmployeesNumber < 50

UPDATE Transactions
SET Price = Price + 50000
WHERE Date > '2023-10-20'

UPDATE Transactions
SET Date = '2023-1-1'
WHERE DepartmentID = 2

UPDATE City
SET BudgetID = 2
WHERE Population > 100000

UPDATE City
SET BudgetID = 1
WHERE Surface < 100000

UPDATE Project
SET ProjectName = 'Sanatate'
WHERE StartDate = '2022-5-4'

UPDATE Position
SET Salary = Salary + 2000
WHERE EducationLevel = 'PhD'

UPDATE Supplier
SET Revenue = Revenue + 10000
WHERE DATEDIFF(year, '2024-10-10', FoundingDate) > 1

UPDATE Supplier
SET SupplierName = 'Supplier6'
WHERE Revenue < 10000

UPDATE Sponsorship
SET Value = Value + 20000
WHERE Value < 10000

UPDATE Sponsorship
SET SponsorName = 'FNI'
WHERE SponsorName = 'FMI'

UPDATE Project
SET ProjectName = 'Cadastru'
WHERE StartDate > '2025-1-1'

UPDATE Project
SET EndDate = '2026-1-1'
WHERE StartDate = '2024-1-1'

UPDATE EmployeeProject
SET EmployeeID = 1
WHERE ProjectID = 2

UPDATE EmployeeProject
SET ProjectID = 5
WHERE EmployeeID = 2

UPDATE Employee
SET Name = 'Gosa Bogdan'
WHERE Name = 'Foica Serban'

UPDATE Employee
SET Name = 'Draguta Vasile'
WHERE Name = 'David Liviu'

-- DELETE

DELETE FROM Employee
WHERE DepartmentID = 2

DELETE FROM Employee
WHERE DepartmentID = 1

DELETE FROM City
WHERE CityName = 'Ialomita'

DELETE FROM City
WHERE Population = 50000

DELETE FROM Budget
WHERE BudgetID = 6

DELETE FROM Budget
WHERE TotalValue = 150

DELETE FROM Department
WHERE EmployeesNumber < 30

DELETE FROM Department
WHERE EmployeesNumber > 10 AND EmployeesNumber < 20

DELETE FROM Transactions
WHERE Price = 20000

DELETE FROM Transactions
WHERE Date > '2024-9-20'

DELETE FROM Position
WHERE EducationLevel = 'PhD' AND Salary = 20000

DELETE FROM Position
WHERE EducationLevel = 'Licenta' AND PositionName = 'Economist'

DELETE FROM Sponsorship
WHERE Value > 100000 AND Value < 130000

DELETE FROM Sponsorship
WHERE SponsorName = 'ASG'

DELETE FROM Supplier
WHERE Revenue > 50000 AND Revenue < 10000

DELETE FROM Supplier
WHERE Revenue = 1000000

DELETE FROM EmployeeProject
WHERE EmployeeID = 4

DELETE FROM EmployeeProject
WHERE ProjectID = 5

DELETE FROM Project
WHERE ProjectName = 'Funding'

DELETE FROM Project
WHERE EndDate = '2025-1-1'

-- Union

SELECT CityName
FROM City
WHERE Population > 10000
UNION ALL
SELECT DepartmentName
FROM Department
WHERE EmployeesNumber > 75

SELECT DepartmentID
FROM Transactions
WHERE Price > 30000 OR DepartmentID = 2
UNION
SELECT PositionID
FROM Position
WHERE EducationLevel = 'Master'

-- Intersect and In

SELECT EmployeeID
FROM Employee
WHERE DepartmentID = 2
INTERSECT
SELECT TransactionID
FROM Transactions
WHERE DepartmentID = 2

SELECT Name
FROM Employee
WHERE EmployeeID IN (
        SELECT EmployeeID
        FROM EmployeeProject
        WHERE ProjectID = 2
    )

-- Except and Not In

SELECT DepartmentName
FROM Department
WHERE DepartmentName IN ('Urbanizare', 'Sanatate', 'Permacultura')
EXCEPT
SELECT DepartmentName
FROM Department
WHERE EmployeesNumber > 50 AND EmployeesNumber < 100

SELECT DepartmentName
FROM Department
WHERE DepartmentID NOT IN (
        SELECT DepartmentID
        FROM Department
        WHERE EmployeesNumber < 100
    )

-- Select

SELECT * FROM Budget
SELECT * FROM City
SELECT * FROM Department
SELECT * FROM Transactions
SELECT * FROM Position
SELECT * FROM Supplier
SELECT * FROM Sponsorship
SELECT * FROM Project
SELECT * FROM Employee
SELECT * FROM EmployeeProject
