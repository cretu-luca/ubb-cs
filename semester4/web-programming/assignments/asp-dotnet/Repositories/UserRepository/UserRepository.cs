using asp_dotnet.Models;
using Microsoft.EntityFrameworkCore;

namespace asp_dotnet.Repository
{
    public class UserRepository : BaseRepository<User>, IUserRepository
    {
        public UserRepository(ApplicationDatabaseContext context) : base(context)
        {
        }

        public User? GetByUsername(string username)
        {
            return context.Users.FirstOrDefault(user => user.Username == username);
        }
    }
} 