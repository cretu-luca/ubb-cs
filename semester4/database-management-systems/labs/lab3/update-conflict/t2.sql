USE CityPlanning

ALTER DATABASE CityPlanning SET ALLOW_SNAPSHOT_ISOLATION ON
ALTER DATABASE CityPlanning SET ALLOW_SNAPSHOT_ISOLATION OFF

SET TRANSACTION ISOLATION LEVEL SNAPSHOT

BEGIN TRAN
    SELECT * FROM Employee
    WHERE EmployeeID = 13

    WAITFOR DELAY '00:00:10'

    SELECT * FROM Employee
    WHERE EmployeeID = 1

    UPDATE dbo.Employee
    SET CityPlanning.dbo.Employee.Name = 'Lavid Diviu'
    WHERE CityPlanning.dbo.Employee.EmployeeID = 13

COMMIT TRAN
