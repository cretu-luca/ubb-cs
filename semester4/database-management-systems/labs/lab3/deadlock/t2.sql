USE CityPlanning

SET DEADLOCK_PRIORITY LOW
SET DEADLOCK_PRIORITY HIGH

BEGIN TRAN
    UPDATE dbo.Project
    SET CityPlanning.dbo.Project.ProjectName = 'Educatie T2'
    WHERE CityPlanning.dbo.Project.ProjectID = 10

    WAITFOR DELAY '00:00:10'

    UPDATE dbo.Employee
    SET CityPlanning.dbo.Employee.Name = 'Luca T2'
    WHERE CityPlanning.dbo.Employee.EmployeeID = 1

COMMIT TRAN
