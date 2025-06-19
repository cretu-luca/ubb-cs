namespace asp_dotnet.Models
{
    public class Ingredient
    {
        public int IngredientID { get; set; }
        public string? Name { get; set; }
        public int Quantity { get; set; }
        public string? MeasurementUnit { get; set; }
        public int RecipeId { get; set; }
    }
}