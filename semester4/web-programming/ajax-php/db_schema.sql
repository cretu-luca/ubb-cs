CREATE DATABASE RecipesDatabase;

USE RecipesDatabase;

CREATE TABLE Recipe (
    RecipeID INT AUTO_INCREMENT,
    Name VARCHAR(50),
    Author VARCHAR(50),
    Type VARCHAR(50),
    Instructions VARCHAR(1024),
    PRIMARY KEY (RecipeID)
);

CREATE TABLE Ingredient (
    IngredientID INT AUTO_INCREMENT,
    Name VARCHAR(50),
    Quantity INT,
    MeasurementUnit VARCHAR(10),
    RecipeID INT,
    PRIMARY KEY (IngredientID),
    FOREIGN KEY (RecipeID) REFERENCES Recipe (RecipeID) ON DELETE CASCADE
);

DROP TABLE Recipe;
DROP TABLE Ingredient;

INSERT INTO Recipe (Name, Author, Type, Instructions)
VALUES ('Pasta', 'Luca', 'Second Course', 'Boil for 8 minutes, then add the sauce.'),
       ('Pizza', 'Serban', 'Second Course', 'Apply the salami then bake for 30 minutes.'),
       ('Tomato soup', 'Denis', 'Main Course', 'Blend the tomatoes and then boil them.'),
       ('Steak', 'Cristi', 'Second Course', 'Fry for 20 minutes while adding herbs.'),
       ('Tiramisu', 'David', 'Dessert', 'Keep in the refrigerator for 6 hours.'),
       ('Onion soup', 'Bogdan', 'Main Course', 'Blend the onion and then boil them'),
       ('Cheesecake', 'Vasile', 'Dessert', 'Keep in the refrigerator for 10 hours');

INSERT INTO Ingredient (Name, Quantity, MeasurementUnit, RecipeID)
VALUES ('Tomatoes', 1, 'Kg', 1),
       ('Tomatoes', 2, 'Kg', 2),
       ('Tomatoes', 3, 'Kg', 3),
       ('Salami', 500, 'g', 2),
       ('Sour Cream', 500, 'ml', 3),
       ('Sour Cream', 300, 'ml', 5),
       ('Sour Cream', 600, 'ml', 7),
       ('Beef', 400, 'g', 4),
       ('Onion', 2, 'Kg', 6),
       ('Berries', 200, 'g', 7),
       ('Herbs', 100, 'g', 4),
       ('Pasta', 400, 'g', 1),
       ('Rum', 80, 'ml', 5),
       ('Butter', 100, 'g', 6);

SELECT * FROM Recipe;
SELECT * FROM Ingredient;