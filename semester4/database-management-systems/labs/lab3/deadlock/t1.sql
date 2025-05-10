USE CityPlanning

SELECT * FROM dbo.Employee
SELECT * FROM dbo.Project

BEGIN TRAN
    UPDATE dbo.Employee
    SET CityPlanning.dbo.Employee.Name = 'Luca T1'
    WHERE CityPlanning.dbo.Employee.EmployeeID = 1

    WAITFOR DELAY '00:00:10'

    UPDATE dbo.Project
    SET CityPlanning.dbo.Project.ProjectName = 'Educatie T1'
    WHERE CityPlanning.dbo.Project.ProjectID = 10

COMMIT TRAN
