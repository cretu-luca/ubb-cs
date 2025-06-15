using Microsoft.AspNetCore.Mvc.RazorPages;
using asp_dotnet.Model;
using System.Text.Json;

namespace server_dotnet.Pages
{
    public class MyProjectsModel : PageModel
    {
        private readonly HttpClient _httpClient;

        public List<Project> Projects { get; set; } = new();

        public MyProjectsModel(IHttpClientFactory httpClientFactory)
        {
            _httpClient = httpClientFactory.CreateClient();
        }

        public async Task OnGetAsync()
        {
            try
            {
                // Copy cookies from the current request to the HTTP client
                var cookieHeader = Request.Headers["Cookie"].ToString();
                if (!string.IsNullOrEmpty(cookieHeader))
                {
                    _httpClient.DefaultRequestHeaders.Add("Cookie", cookieHeader);
                }

                var response = await _httpClient.GetAsync("http://localhost:5262/Project/GetAll");
                if (response.IsSuccessStatusCode)
                {
                    var json = await response.Content.ReadAsStringAsync();
                    var allProjects = JsonSerializer.Deserialize<List<Project>>(json, new JsonSerializerOptions { PropertyNameCaseInsensitive = true }) ?? new();
                    
                    // Filter projects for current user
                    var userId = User.FindFirst("UserId")?.Value;
                    if (!string.IsNullOrEmpty(userId))
                    {
                        Projects = allProjects.Where(p => p.Members.Contains(userId)).ToList();
                    }
                    else
                    {
                        Projects = allProjects; // Show all if no user ID found
                    }
                }
            }
            catch (Exception)
            {
                Projects = new();
            }
        }
    }
} 