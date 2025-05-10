USE CityPlanning

DELETE FROM dbo.Project
WHERE CityPlanning.dbo.Project.ProjectName = 'Educatie'

BEGIN TRAN
    WAITFOR DELAY '00:00:04'

    INSERT INTO dbo.Project (ProjectName, StartDate, EndDate, SupplierID, SponsorshipID)
    VALUES ('Educatie', '01-01-2024', '01-01-2025', 1, 1)

COMMIT TRAN
