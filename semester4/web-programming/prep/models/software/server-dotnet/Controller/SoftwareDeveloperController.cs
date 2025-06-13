using asp_dotnet.Repository;
using asp_dotnet.Model;
using Microsoft.AspNetCore.Mvc;

namespace asp_dotnet.Controller
{
    [Route("[controller]")]
    [ApiController]
    public class SoftwareDeveloperController : BaseController<SoftwareDeveloper>
    {
        public SoftwareDeveloperController(ISoftwareDeveloperRepository repository) : base(repository)
        {
        }
    }
} 