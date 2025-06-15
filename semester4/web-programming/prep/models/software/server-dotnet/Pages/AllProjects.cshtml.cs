using Microsoft.AspNetCore.Mvc.RazorPages;
using asp_dotnet.Model;
using System.Text.Json;

namespace server_dotnet.Pages
{
    public class AllProjectsModel : PageModel
    {
        private readonly HttpClient _httpClient;

        public List<Project> Projects { get; set; } = new();

        public AllProjectsModel(IHttpClientFactory httpClientFactory)
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
                    Projects = JsonSerializer.Deserialize<List<Project>>(json, new JsonSerializerOptions { PropertyNameCaseInsensitive = true }) ?? new();
                }
            }
            catch (Exception)
            {
                Projects = new();
            }
        }
    }
} 