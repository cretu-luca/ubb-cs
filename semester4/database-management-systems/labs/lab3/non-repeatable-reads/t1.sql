USE CityPlanning

SELECT * FROM dbo.Project

INSERT INTO dbo.Project (ProjectName, StartDate, EndDate, SupplierID, SponsorshipID)
VALUES ('Educatie', '01-01-2024', '01-01-2025', 1, 1)

BEGIN TRAN
    WAITFOR DELAY '00:00:05'

    UPDATE dbo.Project
    SET CityPlanning.dbo.Project.EndDate = '01-01-2026'
    WHERE CityPlanning.dbo.Project.ProjectName = 'Educatie'

COMMIT TRAN
