using asp_dotnet.Model;
using Microsoft.EntityFrameworkCore;

namespace asp_dotnet.Repository
{
    public class SoftwareDeveloperRepository : BaseRepository<SoftwareDeveloper>, ISoftwareDeveloperRepository
    {
        public SoftwareDeveloperRepository(ApplicationDatabaseContext context) : base(context)
        {
        }

        public async Task<SoftwareDeveloper?> GetSoftwareDeveloperByUsername(string username)
        {
            return await this.context.SoftwareDeveloper
                .Where(developer => developer.Name == username)
                .FirstOrDefaultAsync();
        }
    }
}