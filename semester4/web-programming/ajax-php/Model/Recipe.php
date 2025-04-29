<?php
    class Recipe {
        public $RecipeID;
        public $Name; 
        public $Author;
        public $Type;
        public $Instructions;

        public function isValid() {
            return !empty($this->Name) && 
                !empty($this->Author) && 
                !empty($this->Type) && 
                !empty($this->Instructions);
        }
    }
?>