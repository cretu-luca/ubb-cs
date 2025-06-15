using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;
using asp_dotnet.Model;
using System.Text.Json;

namespace server_dotnet.Pages
{
    public class AllDevelopersModel : PageModel
    {
        private readonly HttpClient _httpClient;

        [BindProperty]
        public string SkillFilter { get; set; } = "";
        
        public List<SoftwareDeveloper> FilteredDevelopers { get; set; } = new();

        public AllDevelopersModel(IHttpClientFactory httpClientFactory)
        {
            _httpClient = httpClientFactory.CreateClient();
        }

        public async Task OnGetAsync()
        {
            await LoadDevelopers();
        }

        public async Task<IActionResult> OnPostAsync()
        {
            await LoadDevelopers();
            return Page();
        }

        private async Task LoadDevelopers()
        {
            try
            {
                // Copy cookies from the current request to the HTTP client
                var cookieHeader = Request.Headers["Cookie"].ToString();
                if (!string.IsNullOrEmpty(cookieHeader))
                {
                    _httpClient.DefaultRequestHeaders.Add("Cookie", cookieHeader);
                }

                var response = await _httpClient.GetAsync("http://localhost:5262/SoftwareDeveloper/GetAll");
                if (response.IsSuccessStatusCode)
                {
                    var json = await response.Content.ReadAsStringAsync();
                    var allDevelopers = JsonSerializer.Deserialize<List<SoftwareDeveloper>>(json, new JsonSerializerOptions { PropertyNameCaseInsensitive = true }) ?? new();
                    
                    if (string.IsNullOrEmpty(SkillFilter))
                    {
                        FilteredDevelopers = allDevelopers;
                    }
                    else
                    {
                        FilteredDevelopers = allDevelopers.Where(d => d.Skills.Contains(SkillFilter, StringComparison.OrdinalIgnoreCase)).ToList();
                    }
                }
            }
            catch (Exception)
            {
                FilteredDevelopers = new();
            }
        }
    }
} 