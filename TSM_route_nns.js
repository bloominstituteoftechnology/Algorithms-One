const Cities =  require('./cities');
const distance_between = require('./distance');

function TSM_route_nns() {
    let 
    count = 0;
    const City = (x, y) => {
        this.x = x;
        this.y = y;
    } 

    for(let i = 0 ; i < Cities.length-1; i++) {
        Cities[i] = new City();
        distance_between(Cities[i], Cities[i+1]);
    }
    return Cities;

    
}