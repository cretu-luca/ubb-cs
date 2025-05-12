USE CityPlanning

SELECT * FROM Employee;

WAITFOR DELAY '00:00:10'

BEGIN TRAN
    UPDATE dbo.Employee
    SET CityPlanning.dbo.Employee.Name = 'Lavid Diviu'
    WHERE CityPlanning.dbo.Employee.EmployeeID = 13

    WAITFOR DELAY '00:00:10'

COMMIT TRAN

UPDATE Employee
SET Name = 'Genis Denolea'
WHERE EmployeeID = 3

SELECT * FROM Employee;
