class User{    
    constructor(id, nome, username, hash) {
        if(id)
            this.id = id;

        this.nome = nome;
        this.username = username;
        this.hash = hash;
    }
}

module.exports = User;