using Microsoft.AspNetCore.Mvc;
using asp_dotnet.Repository;

namespace asp_dotnet.Controllers
{
    [Route("[controller]")]
    [ApiController]
    public class BaseController<T> : ControllerBase where T : class
    {
        private IRepository<T> repository;

        public BaseController(IRepository<T> repository)
        {
            this.repository = repository;
        }

        [HttpGet]
        public async Task<ActionResult<IEnumerable<T>>> GetAll()
        {
            var entities = await this.repository.GetAllAsync();
            return Ok(entities);
        }

        [HttpGet("{id}")]
        public async Task<ActionResult<T>> GetById(int id)
        {
            var entity = await repository.GetByIdAsync(id);
            if (entity == null)
            {
                return NotFound();
            }
            return Ok(entity);
        }

        [HttpPost]
        public async Task<ActionResult<T>> Create([FromBody] T entity)
        {
            var created = await repository.AddAsync(entity);
            return Ok(created);
        }

        [HttpPut]
        public async Task<ActionResult<T>> Update([FromBody] T entity)
        {
            await repository.UpdateAsync(entity);
            return Ok(entity);
        }

        [HttpDelete("{id}")]
        public async Task<ActionResult> Delete(int id)
        {
            await repository.DeleteAsync(id);
            return Ok(id);
        }
    }
}