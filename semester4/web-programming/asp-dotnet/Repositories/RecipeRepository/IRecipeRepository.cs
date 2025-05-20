using asp_dotnet.Models;

namespace asp_dotnet.Repository;

public interface IRecipeRepository : IBaseRepository<Recipe>
{
    public Task<IEnumerable<Recipe>> GetRecipesByAuthor(string author);
    public Task<IEnumerable<Recipe>> GetRecipesByType(string type);
}