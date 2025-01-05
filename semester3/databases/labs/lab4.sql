-- 2 queries with a subquery in the FROM clause
SELECT CityName, Population
FROM (
    SELECT CityName, Population
    FROM City
    WHERE Population > (SELECT AVG(Population)
                        FROM City)
) as CityInformation
WHERE CityName NOT IN ('Timisoara', 'Bucuresti')

select * from City

SELECT EducationStats.EducationLevel, AVG(EducationStats.Salary)
FROM (
    SELECT EducationLevel, Salary
    FROM Position
) as EducationStats
GROUP by EducationStats.EducationLevel

-- 4 queries with the GROUP BY clause
SELECT DepartmentName, COUNT(*)
FROM Department
JOIN Employee ON Employee.DepartmentID = Department.DepartmentID
GROUP BY DepartmentName

SELECT BudgetID, COUNT(*)
FROM City
GROUP BY BudgetID
HAVING COUNT(*) > 1

SELECT SponsorName, SUM(Value)
FROM Sponsorship
GROUP BY SponsorName
HAVING SUM(Value) > 100000

SELECT DepartmentID, AVG(Price)
FROM Transactions
GROUP BY DepartmentID
HAVING AVG(Price) > (
    SELECT AVG(Price)
    FROM Transactions
) AND SUM(Price) / 12 > 1000

select * from Transactions

-- 4 queries using ANY and ALL to introduce a subquery in the WHERE clause
SELECT PositionName, Salary
FROM Position
WHERE Salary > ANY (
    SELECT Salary
    FROM Position
    WHERE PositionName IN ('Admin IT', 'Marketing Expert')
) ORDER BY Salary DESC

SELECT PositionName, Salary
FROM Position
WHERE Salary > (
    SELECT MIN(Salary)
    FROM Position
    WHERE PositionName IN ('Admin IT', 'Marketing Expert')
) ORDER BY Salary DESC

SELECT TOP 3 CityName, Population
FROM City
WHERE Population > ALL (
    SELECT Population
    FROM City
    WHERE Population < 200000
) ORDER BY Population

SELECT TOP 3 CityName, Population
FROM City
WHERE Population > (
    SELECT MAX(Population)
    FROM City
    WHERE Population < 200000
) ORDER BY Population

SELECT DepartmentName, EmployeesNumber
FROM Department
WHERE EmployeesNumber > ANY (
    SELECT EmployeesNumber
    FROM Department
    WHERE EmployeesNumber >= 100
)

SELECT DepartmentName, MAX(EmployeesNumber)
FROM Department
WHERE EmployeesNumber NOT IN (
    SELECT EmployeesNumber
    FROM Department
    WHERE EmployeesNumber <= 100
)
GROUP BY DepartmentName

SELECT PositionName, PositionID
FROM Position
WHERE PositionID IN (SELECT PositionID
                     FROM Position
                     WHERE Salary > ANY (SELECT Salary
                                     FROM Position))

SELECT PositionName, PositionID
FROM Position
WHERE PositionID NOT IN (SELECT PositionID
                     FROM Position
                     WHERE Salary <= (SELECT MIN(Salary)
                                     FROM Position))

SELECT DISTINCT EducationLevel
FROM Position
WHERE PositionID NOT IN (SELECT PositionID
                     FROM Position
                     WHERE Salary <= (SELECT MIN(Salary)
                                     FROM Position))


SELECT DISTINCT EducationLevel
FROM Position
WHERE PositionID IN (SELECT PositionID
                     FROM Position
                     WHERE Salary > ANY (SELECT Salary
                                     FROM Position))

SELECT * FROM Position

