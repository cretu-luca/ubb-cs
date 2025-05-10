<?php
    class Ingredient {
        public $IngredientID;
        public $Name;
        public $Quantity;
        public $MeasurementUnit;
        public $RecipeID;

        public function isValid() {
            return !empty($this->Name) && 
                   $this->Quantity > 0 && 
                   !empty($this->MeasurementUnit) && 
                   !empty($this->RecipeID);
        }
    }
?> 