using asp_dotnet.Model;

namespace asp_dotnet.Repository
{
    public interface ISoftwareDeveloperRepository : IBaseRepository<SoftwareDeveloper>
    {
        public Task<SoftwareDeveloper?> GetSoftwareDeveloperByUsername(string username);
    };
}