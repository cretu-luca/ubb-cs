using System.ComponentModel;
using System.ComponentModel.DataAnnotations;

namespace asp_dotnet.Model;

public class Project
{
    [Key]
    public int Id { get; set; }
    public int ProjectManagerID { get; set; }
    public string Name { get; set; }
    public string Description { get; set; }
    public string Members { get; set; }
}