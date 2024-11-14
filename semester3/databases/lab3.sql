-- inner join - joins 3 tables --
SELECT DepartmentID, DepartmentName
FROM Department D
INNER JOIN dbo.City C on D.CityID = C.CityID
INNER JOIN dbo.Budget B on C.BudgetID = B.BudgetID
WHERE C.Population > 1000000 AND B.TotalValue > 50

-- full join - joins 2 many-to-many relationships --
SELECT ProjectName
FROM Project P
FULL JOIN dbo.EmployeeProject EP on P.ProjectID = EP.ProjectID
FULL JOIN dbo.Employee E on E.EmployeeID = EP.EmployeeID
WHERE ProjectName IN ('HealthCare', 'Urbanism') AND E.EmployeeID IN (
        SELECT E.EmployeeID
        FROM Employee
        WHERE E.DepartmentID in (
                SELECT E.DepartmentID
                FROM Department
                WHERE EmployeesNumber = 10
            )
    )

SELECT * FROM Project, Employee, Department

SELECT *  FROM Employee
SELECT * FROM Department
-- left join --
SELECT TransactionID, Date
FROM Transactions T
LEFT JOIN dbo.Department D on D.DepartmentID = T.DepartmentID
WHERE D.EmployeesNumber > 70

-- right join --
SELECT P.PositionID, PositionName
FROM Position P
RIGHT JOIN dbo.Employee E on P.PositionID = E.PositionID
WHERE EducationLevel IN ('MASTERS', 'PhD') AND E.EmployeeID in (
        SELECT E.EmployeeID
        FROM Employee
        WHERE E.DepartmentID in (
                SELECT E.DepartmentID
                FROM Department
                WHERE DepartmentName IN ('Agricultura', 'Sanatate')
            )
    )

-- the IN operator (WHERE inside WHERE inside WHERE) --
SELECT CityName
FROM City C
WHERE BudgetID IN (
        SELECT B.BudgetID
        FROM Budget B
        JOIN City ON B.BudgetID = City.BudgetID
        WHERE CityID IN (
                SELECT CityID
                FROM Department D
                WHERE DepartmentName IN ('Siguranta nationala')
            )
    )

SELECT * FROM City
select * from Budget
SELECT * FROM Department

SELECT B.BudgetID
FROM Budget B
JOIN City ON B.BudgetID = City.BudgetID
WHERE CityID IN (
        SELECT CityID
        FROM Department D
        WHERE DepartmentName IN ('Siguranta nationala')
    )

SELECT CityID
        FROM Department D
        WHERE DepartmentName IN ('Siguranta nationala')


SELECT * FROM City
SELECT * FROM Department
SELECT * FROM Budget

SELECT ProjectName
FROM Project P
WHERE P.SponsorshipID IN (
        SELECT SponsorshipID
        FROM Sponsorship S
        WHERE S.Value > 50000
    )

-- exists and where --
SELECT ProjectName
FROM Project P
WHERE EXISTS (
    SELECT EmployeeID
    FROM EmployeeProject
    WHERE EmployeeID = 5
)

SELECT SupplierName
FROM Supplier S
WHERE EXISTS (
    SELECT ProjectID
    FROM Project P
    WHERE P.EndDate < '6-6-2024'
)

select * from Supplier
select * from Project
