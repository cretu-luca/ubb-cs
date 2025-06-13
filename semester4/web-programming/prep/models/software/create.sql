CREATE DATABASE Software;

USE Software;

CREATE TABLE SoftwareDeveloper (
    Id INT PRIMARY KEY AUTO_INCREMENT,
    Name VARCHAR (50),
    Age INT,
    Skills VARCHAR (50)
);

DROP TABLE SoftwareDeveloper;

CREATE TABLE Project (
    Id INT PRIMARY KEY AUTO_INCREMENT,
    ProjectManagerId INT,
    Name VARCHAR (50),
    Description VARCHAR (50),
    Members VARCHAR (50),
    FOREIGN KEY (ProjectManagerId) REFERENCES SoftwareDeveloper (id)
);

DROP TABLE Project;

INSERT INTO SoftwareDeveloper (Id, Name, Age, Skills) VALUES (1, 'Luca', 20, 'Skill_1, Skill_2'),
                                                             (2, 'Denis', 19, 'Skill_3, Skill_4')

SELECT * FROM SoftwareDeveloper;

INSERT INTO Project (Id, ProjectManagerId, Name, Description, Members) VALUES (1, 1, 'Project_1', 'Good', '1, 2'),
                                                                              (2, 2, 'Project_2', 'Bad', '1')

SELECT * FROM Project;