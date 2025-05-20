namespace asp_dotnet.Models
{
    public class Recipe
    {
        public int RecipeID { get; set; }
        public string Name { get; set; }
        public string Author { get; set; }
        public string Type { get; set; }
        public string Instructions { get; set; }
        public DateOnly Date { get; set; }
    }
}
