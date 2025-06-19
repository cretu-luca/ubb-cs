using asp_dotnet.Models;

namespace asp_dotnet.Repository
{
    public interface IUserRepository : IBaseRepository<User>
    {
        User? GetByUsername(string username);
    }
} 