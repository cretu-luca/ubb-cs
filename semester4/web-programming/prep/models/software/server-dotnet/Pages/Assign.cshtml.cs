using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;
using System.Text.Json;
using System.Text;

namespace server_dotnet.Pages
{
    public class AssignModel : PageModel
    {
        private readonly HttpClient _httpClient;

        [BindProperty]
        public string UserId { get; set; } = "";
        
        [BindProperty]
        public string ProjectNames { get; set; } = "";
        
        [TempData]
        public string Message { get; set; } = "";

        public AssignModel(IHttpClientFactory httpClientFactory)
        {
            _httpClient = httpClientFactory.CreateClient();
        }

        public void OnGet()
        {
            // Just display the assign page
        }

        public async Task<IActionResult> OnPostAsync()
        {
            try
            {
                if (string.IsNullOrEmpty(UserId) || string.IsNullOrEmpty(ProjectNames))
                {
                    Message = "User ID and project names are required";
                    return Page();
                }

                // Copy cookies from the current request to the HTTP client
                var cookieHeader = Request.Headers["Cookie"].ToString();
                if (!string.IsNullOrEmpty(cookieHeader))
                {
                    _httpClient.DefaultRequestHeaders.Add("Cookie", cookieHeader);
                }

                var assignRequest = new { userid = UserId, projectNames = ProjectNames };
                var json = JsonSerializer.Serialize(assignRequest);
                var content = new StringContent(json, Encoding.UTF8, "application/json");

                var response = await _httpClient.PostAsync("http://localhost:5262/Project/Assign", content);
                
                if (response.IsSuccessStatusCode)
                {
                    var responseContent = await response.Content.ReadAsStringAsync();
                    Message = responseContent.Trim('"'); // Remove quotes from JSON string response
                    return RedirectToPage("/AllProjects"); // Redirect to see the results
                }
                else
                {
                    Message = "Error assigning user to projects";
                    return Page();
                }
            }
            catch (Exception ex)
            {
                Message = $"Error: {ex.Message}";
                return Page();
            }
        }
    }
} 