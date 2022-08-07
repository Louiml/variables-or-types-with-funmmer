fn hashpassword(password: &str) -> String {
    let mut hasher = Sha256::new();
    hasher.input_str(password);
    let hash = hasher.result_str();
    return hash;
}
